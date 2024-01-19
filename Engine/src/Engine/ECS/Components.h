#pragma once

#include "Base.h"
#include "Engine/Graphics/Textures/TextureProperties.h"
#include "Engine/Graphics/GraphicsProperties.h"
#include "Engine/Physics/PhysicsProperties.h"

#include <glm/gtc/quaternion.hpp>

namespace MyEngine
{
	struct TagComponent
	{
		std::string name;
	};

	struct TransformComponent
	{
		glm::vec3 position;
		glm::quat orientation;
		float scale;

		// Values calculated in relation to parent
		glm::vec3 worldPosition;
		glm::quat worldOrientation;
		float worldScale;

		// Value calculated distance in relation to camera position
		float distToCamera;
	};

	struct MovementComponent
	{
		glm::vec3 velocity;
		glm::vec3 acceleration;
	};

	struct RotationComponent
	{
		glm::vec3 velocity;
		glm::vec3 acceleration;
	};

	struct ParentComponent
	{
		Entity parentId;
	};

	struct TextureComponent
	{
		std::string fileName;
		eTextureType textureType;

		// Cube map list of texture sides
		std::vector<std::string> vecTextures;
	};

	struct MaterialComponent
	{
		std::string name;

		glm::vec3 offset; // fixed offset

		glm::vec3 currOffset;
		glm::vec3 offsetMove;

		glm::vec3 currOffsetHeightMap;
		glm::vec3 offsetHeightMap;

		std::vector<std::string> colorTextures;
		glm::vec3 colorTexturesRatios;

		bool useHeightMap;
		std::string heightMapTexture;
		float heightScale;

		bool useNormalTexture;
		std::string normalTexture;

		bool useSpecularTexture;
		std::string specularTexture;

		bool useDiscardTexture;
		std::string discardTexture;

		bool useCubeTexture;
		std::string cubeTexture;

		bool isEmissive;

		// Material transparency
		bool useAlphaTexture;
		std::string alphaTexture;

		std::vector<TextureComponent*> texturesComponents;
	};

	struct LightComponent
	{
		// Flickering control
		glm::vec4 flickerOffset;

		std::string ulBasePath;

		// Controls relative to transform component
		glm::vec4 positionOffset;
		glm::vec4 directionOffset;
		// multiplied by the direction to put the light at N distance from the front of the object
		float distanceOffset;

		// Light parameters
		glm::vec4 diffuse;   // Colour of the light (used for diffuse)
		glm::vec4 specular;  // rgb = highlight colour, w = power
		glm::vec4 atten;	 // x = constant, y = linear, z = quadratic, w = DistanceCutOff
		glm::vec4 initialAtten;
		glm::vec4 direction; // Spot, directional lights
		glm::vec4 params;	 // x = Light::LIGHT_TYPE, y = inner angle, z = outer angle, w = is flickery
		bool status;	     // x = 0 for off, 1 for on

		// Parameters uniform locations
		GLint position_UL;
		GLint diffuse_UL;
		GLint specular_UL;
		GLint atten_UL;
		GLint direction_UL;
		GLint params_UL;
		GLint status_UL;
	};

	struct ModelComponent
	{
		std::vector<std::string> models;
		std::vector <sMesh*> pMeshes;

		std::string material;
		bool isWireframe;
		bool doNotLight;
		bool useColorTexture;

		double elapsedTime;
		bool isActive;
		int currMesh;
	};

	struct TilingComponent
	{
		glm::vec3 axis;
		glm::vec3 offset;
	};

	struct GravityComponent
	{
		glm::vec3 acceleration;
	};

	struct RigidBodyComponent
	{
		eBody bodyType;
		eShape shapeType;
	};

	struct MeshColliderComponent
	{
		std::string name;
		sMesh* pMesh;
	};

	struct SphereColliderComponent
	{
		float radius;
	};

	struct AABBColliderComponent
	{
		glm::vec3 min;
		glm::vec3 max;
	};
}
