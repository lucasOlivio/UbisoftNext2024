// Fragment shader
#version 420

in vec4 colour;
in vec4 vertexWorldPos;			// vertex in "world space"
in vec4 vertexWorldNormal;	
in vec2 textureCoords;
in float height;

out vec4 outputColour;		// To the frame buffer (aka screen)

uniform vec4 eyeLocation;

uniform bool bUseDebugColour;	// if this is true, then use debugColourRGBA for the colour
uniform vec4 debugColourRGBA;	

// TEXTURES
// -----------------------------------------------------------------

uniform bool isEmissive;

uniform vec2 UVOffset;
uniform vec2 HeightMapOffset;

uniform bool bUseColorTexture;		// If false, then use vertex colors instead of texture colours
uniform bool bUseHeightMapTexture;
uniform bool bUseNormalTexture;
uniform bool bUseSpecularTexture;
uniform bool bUseDiscardTexture;
uniform bool bUseAlphaTexture;
uniform bool bUseCubeTexture;

const int NUMBEROFTEXTURES = 4;

uniform sampler2D colorTexture00;
uniform sampler2D colorTexture01;
uniform sampler2D colorTexture02;

uniform float colorTextureRatio00;
uniform float colorTextureRatio01;
uniform float colorTextureRatio02;

uniform sampler2D heightMapTexture;
uniform sampler2D normalTexture;
uniform sampler2D specularTexture;
uniform sampler2D discardTexture;
uniform sampler2D alphaTexture;
uniform samplerCube cubeTexture;

// LIGHTS
// -----------------------------------------------------------------
uniform bool doNotLight; // If true, then passes the colour without calculating lighting

struct sLight
{
	vec4 position;			
	vec4 diffuse;	// Colour of the light (used for diffuse)
	vec4 specular;	// rgb = highlight colour, w = power
	vec4 atten;		// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	vec4 direction;	// Spot, directional lights
	vec4 params;	// x = lightType, y = inner angle, z = outer angle, w = TBD
	                // 0 = pointlight
					// 1 = spot light
					// 2 = directional light
	bool status;	// x = 0 for off, 1 for on
};

const int POINT_LIGHT_TYPE = 0;
const int SPOT_LIGHT_TYPE = 1;
const int DIRECTIONAL_LIGHT_TYPE = 2;

// This should match with the number in the constants
const int NUMBEROFLIGHTS = 40;
uniform sLight theLights[NUMBEROFLIGHTS];


vec4 calculateLightContrib( vec3 vertexMaterialColour, vec3 vertexNormal, 
                            vec3 vertexWorldPos, vec4 vertexSpecular );

vec3 calculateColorTextures(vec2 UVFinal);

void main()
{
	vec2 UVFinal = textureCoords.st + UVOffset.yx;

	if (bUseCubeTexture)
	{
		vec4 cubeSampleColour = texture(cubeTexture, vertexWorldNormal.xyz).rgba;
		outputColour.rgb = cubeSampleColour.rgb;
		outputColour.a = 1.0f;
		return;
	}

	if (bUseDebugColour)
	{
		outputColour = debugColourRGBA;
		return;
	}

	// Use model vertex as default
	vec4 vertexRGBA = colour;
	vertexRGBA.a = 1.0;

	if (bUseAlphaTexture)
	{
		vertexRGBA.a = texture(alphaTexture, UVFinal.st).r;
		if (vertexRGBA.a < 0.3)
		{
			discard;
		}
	}
	
	if (bUseColorTexture)
	{
		vertexRGBA.rgb = calculateColorTextures(UVFinal);
	}

	if (bUseDiscardTexture)
	{
		float discardValue = texture(discardTexture, UVFinal.st).r;
		if (discardValue < 0.1)
		{
			discard;
		}
	}
	
	if ( doNotLight )
	{
		outputColour = vertexRGBA;
		return;
	}
	
	// *************************************
	vec4 vertexSpecular = vec4(0.1f, 0.1f, 0.1f, 1.0f);
	if (bUseSpecularTexture)
	{
		vertexSpecular = texture(specularTexture, UVFinal.st).rgba;
	}

	// xyzw or rgba or stuw
	// RGB is the specular highglight colour (usually white or the colour of the light)
	// 4th value is the specular POWER (STARTS at 1, and goes to 1000000s)
	
	vec4 vertexColourLit = calculateLightContrib( vertexRGBA.rgb, vertexWorldNormal.xyz, 
	                                              vertexWorldPos.xyz, vertexSpecular );
	// *************************************

	// TODO: Add an emissive map and emissive intensity regulator
	// For now we control it here for simplicity
	if (isEmissive)
	{
		vertexColourLit.rgb = vertexColourLit.rgb + (vertexRGBA.rgb * 0.75);
	}
			
	outputColour.rgb = vertexColourLit.rgb;
	outputColour.a = vertexRGBA.a;
	return;
}

vec4 calculateLightContrib( vec3 vertexMaterialColour, vec3 vertexNormal, 
                            vec3 vertexWorldPos, vec4 vertexSpecular )
{
	vec3 norm = normalize(vertexNormal);
	
	vec4 finalObjectColour = vec4( 0.0f, 0.0f, 0.0f, 1.0f );
	
	for ( int index = 0; index < NUMBEROFLIGHTS; index++ )
	{	
		// ********************************************************
		// is light "on"
		if ( !theLights[index].status )
		{	// it's off
			continue;
		}
		
		// Cast to an int (note with c'tor)
		int intLightType = int(theLights[index].params.x);
		
		// We will do the directional light here... 
		// (BEFORE the attenuation, since sunlight has no attenuation, really)
		if ( intLightType == DIRECTIONAL_LIGHT_TYPE )		// = 2
		{
			// This is supposed to simulate sunlight. 
			// SO: 
			// -- There's ONLY direction, no position
			// -- Almost always, there's only 1 of these in a scene
			// Cheapest light to calculate. 

			vec3 lightContrib = theLights[index].diffuse.rgb;
			
			// Get the dot product of the light and normalize
			float dotProduct = dot( -theLights[index].direction.xyz,  
									   normalize(norm.xyz) );	// -1 to 1

			dotProduct = max( 0.0f, dotProduct );		// 0 to 1
		
			lightContrib *= dotProduct;		
			
			finalObjectColour.rgb += (vertexMaterialColour.rgb * theLights[index].diffuse.rgb * lightContrib); 
									 //+ (materialSpecular.rgb * lightSpecularContrib.rgb);
			// NOTE: There isn't any attenuation, like with sunlight.
			// (This is part of the reason directional lights are fast to calculate)

			continue;		
		}
		
		// Assume it's a point light 
		// intLightType = 0

		// Contribution for this light
		vec3 vLightToVertex = theLights[index].position.xyz - vertexWorldPos.xyz;
		float distanceToLight = length(vLightToVertex);	
		vec3 lightVector = normalize(vLightToVertex);
		float dotProduct = dot(lightVector, vertexNormal.xyz);	 
		
		dotProduct = max( 0.0f, dotProduct );	
		
		vec3 lightDiffuseContrib = dotProduct * theLights[index].diffuse.rgb;
			

		// Specular 
		vec3 lightSpecularContrib = vec3(0.0f);
			
		vec3 reflectVector = reflect( -lightVector, normalize(norm.xyz) );

		// Get eye or view vector
		// The location of the vertex in the world to your eye
		vec3 eyeVector = normalize(eyeLocation.xyz - vertexWorldPos.xyz);

		// To simplify, we are NOT using the light specular value, just the object’s.
		float objectSpecularPower = vertexSpecular.w; 
		
//		lightSpecularContrib = pow( max(0.0f, dot( eyeVector, reflectVector) ), objectSpecularPower )
//			                   * vertexSpecular.rgb;	//* theLights[lightIndex].Specular.rgb
		lightSpecularContrib = pow( max(0.0f, dot( eyeVector, reflectVector) ), objectSpecularPower )
			                   * theLights[index].specular.rgb;
							   
		// Attenuation
		float attenuation = 1.0f / 
				( theLights[index].atten.x + 										
				  theLights[index].atten.y * distanceToLight +						
				  theLights[index].atten.z * distanceToLight*distanceToLight );  	
				  
		// total light contribution is Diffuse + Specular
		lightDiffuseContrib *= attenuation;
		lightSpecularContrib *= attenuation;
		
		// But is it a spot light
		if ( intLightType == SPOT_LIGHT_TYPE )		// = 1
		{
			// Yes, it's a spotlight
			// Calcualate light vector (light to vertex, in world)
			vec3 vertexToLight = vertexWorldPos.xyz - theLights[index].position.xyz;

			vertexToLight = normalize(vertexToLight);

			float currentLightRayAngle
					= dot( vertexToLight.xyz, theLights[index].direction.xyz );
					
			currentLightRayAngle = max(0.0f, currentLightRayAngle);

			//vec4 params;	
			// x = lightType, y = inner angle, z = outer angle, w = TBD

			// Is this inside the cone? 
			float outerConeAngleCos = cos(radians(theLights[index].params.z));
			float innerConeAngleCos = cos(radians(theLights[index].params.y));
							
			// Is it completely outside of the spot?
			if ( currentLightRayAngle < outerConeAngleCos )
			{
				// Nope. so it's in the dark
				lightDiffuseContrib = vec3(0.0f, 0.0f, 0.0f);
				lightSpecularContrib = vec3(0.0f, 0.0f, 0.0f);
			}
			else if ( currentLightRayAngle < innerConeAngleCos )
			{
				// Angle is between the inner and outer cone
				// (this is called the penumbra of the spot light, by the way)
				// 
				// This blends the brightness from full brightness, near the inner cone
				//	to black, near the outter cone
				float penumbraRatio = (currentLightRayAngle - outerConeAngleCos) / 
									  (innerConeAngleCos - outerConeAngleCos);
									  
				lightDiffuseContrib *= penumbraRatio;
				lightSpecularContrib *= penumbraRatio;
			}
						
		}// if ( intLightType == 1 )
					
		finalObjectColour.rgb += (vertexMaterialColour.rgb * lightDiffuseContrib.rgb)
								  + (vertexSpecular.rgb  * lightSpecularContrib.rgb );

	}//for(intindex=0...
	
	finalObjectColour.a = 1.0f;
	
	return finalObjectColour;
}

vec3 calculateColorTextures(vec2 UVFinal)
{
	vec3 tempColor = vec3(0);
	
	tempColor = texture(colorTexture00, UVFinal.st).rgb * colorTextureRatio00
				+ texture(colorTexture01, UVFinal.st).rgb * colorTextureRatio01
				+ texture(colorTexture02, UVFinal.st).rgb * colorTextureRatio02;

	return tempColor;
}
