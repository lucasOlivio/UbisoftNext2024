#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace MyEngine
{
	class TransformUtils
	{
	public:
        static void ApplyTranslation(const glm::vec3& position, glm::mat4& matModelOut);

        static void ApplyRotation(const glm::quat& qOrientation, glm::mat4& matModelOut);

		static void ApplyScale(const float& scale, glm::mat4& matModelOut);

		static void GetTransform(const glm::vec3& position,
                                 const glm::quat& orientation,
                                 const float& scale, 
                                 glm::mat4& matModelOut);

		static void GetTransform(const glm::vec3& position,
								 const float& scale, 
								 glm::mat4& matModelOut);

		static glm::vec3 GetUpVector(const glm::quat& orientation);
		static glm::vec3 GetForwardVector(const glm::quat& orientation);
		static glm::vec3 GetRightVector(const glm::quat& orientation);

		static glm::quat AdjustOrientation(const glm::quat& orientation, 
										   const glm::vec3& delta);

		static glm::vec3 GetQuatAsDegrees(const glm::quat& orientation);

		static glm::quat GetDegreesAsQuat(const glm::vec3& rotation);

		// Use transformations to convert the point from local to world position
		static glm::vec3 LocalToWorldPoint(const glm::vec3& point,
                                           const glm::vec3& position, const glm::quat& orientation,
                                           const float& scale, 
										   glm::mat4& parentMat = glm::mat4(1.0f));
		static glm::vec3 LocalToWorldPoint(const glm::vec3& point,
										   const glm::vec3& position, const float& scale,
                                           glm::mat4& parentMat = glm::mat4(1.0f));
	};
}
