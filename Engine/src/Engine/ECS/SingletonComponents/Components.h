#pragma once

#include "Engine/Core/Shapes.hpp"
#include "Engine/Core/StateProperties.h"

#include "Engine/ECS/Base.h"
#include "Engine/ECS/Scene/Scene.h"

#include "Engine/Graphics/opengl.h"
#include "Engine/Graphics/Textures/TextureProperties.h"
#include "Engine/Graphics/GraphicsProperties.h"

#include "Engine/Physics/BroadPhase/GridAABB.h"
#include "Engine/Physics/PhysicsProperties.h"

#include "Engine/Utils/TransformUtils.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <map>

namespace MyEngine
{
	// Singleton components
	struct CameraComponent
	{
		glm::vec3 position;
		glm::quat orientation;
		glm::vec3 upVector;

		float distance;
		float height;
		float offsetTarget;

		glm::vec3 FinalPosition()
		{
			using namespace glm;

			vec3 transfUp = TransformUtils::GetUpVector(orientation);
			vec3 transfForward = TransformUtils::GetForwardVector(orientation);

			vec3 offsetDist = -distance * transfForward;
			vec3 offsetHeight = height * transfUp;

			vec3 camFinalPos = position + offsetDist + offsetHeight;

			return camFinalPos;
		}

		glm::mat4 ViewMat()
		{
			using namespace glm;

			// Calculating camera view
			vec3 cameraPosition = FinalPosition();

			vec3 target = position + (TransformUtils::GetForwardVector(orientation) * offsetTarget);

			return lookAt(
				cameraPosition,
				target,
				TransformUtils::GetUpVector(orientation)
			);
		}
	};

	struct WindowComponent
	{
		std::string name;
		int width = 640;
		int height = 480;
		float zNear;
		float zFar;
		float fovy;

		GLFWwindow* pGLFWWindow;

		float Ratio()
		{
			float ratio = 0.0f;
			if (height > 0)
			{
				ratio = width / (float)height;
			}

			return ratio;
		}

		glm::mat4 ProjectionMat()
		{
			return glm::perspective(fovy,
								    Ratio(),
								    zNear,
								    zFar);
		}
	};

	struct ConfigPathComponent
	{
		std::string pathModels;
		std::string pathAudio;
		std::string pathShaders;
		std::string pathScripts;
		std::string pathTextures;
		std::string pathScenes;

		// Path to debug models inside models default folder
		std::string pathDebugSquare; 
		std::string pathDebugSphere;
	};

	struct TransparentEntitiesComponent
	{
		std::vector<Entity> entities;
	};

	struct FrameCounterComponent
	{
		int frameCount;
		float fpsTimer;
		float fps;
	};

	struct GridBroadphaseComponent
	{
		// Mapping of AABBs to their indices in the grid
		std::map< uint /*index*/, GridAABB* > mapAABBs;

		// Length per grid box in the grid
		glm::vec3 lengthPerBox;
	};

	// Generic grouping for any narrow phase testing 
	struct NarrowPhaseTestsComponent
	{
		// Groups of shapes and entities to test,
		// the triangles to be tested against the entities will be in the same index
		std::vector<std::vector<sTriangle*>> trianglesToTest;
		std::vector<std::vector<Entity>> staticEntitiesToTest;
		std::vector<std::vector<Entity>> nonStaticEntitiesToTest;
	};

	// All collisions that happened in the last <FRAME_RATE> frames
	struct FrameCollisionComponent
	{
		std::vector<sCollisionData> collisions[FRAME_RATE];
		size_t currSize;
	};

	struct KeyInputComponent
	{
		// One for each key code from glfw
		bool key[350];
	};

	struct MouseInputComponent
	{
		// One for each mouse button code from glfw
		bool button[7];

		float posX;
		float posY;

		float lastPosX;
		float lastPosY;

		float sensitivity;

		bool mouseCaptured;
	};

	struct StateComponent
	{
		eStates prevState; // Only state system should modify this
		eStates currState; // Any system can modify this to stop/run simulation
	};

	// Debug objects

	struct DebugSquareComponent
	{
		sMesh* pMesh;
	};

	struct DebugSphereComponent
	{
		sMesh* pMesh;
	};
}