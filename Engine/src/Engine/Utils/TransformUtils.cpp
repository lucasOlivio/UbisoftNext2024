#include "pch.h"

#include "TransformUtils.h"

namespace MyEngine
{
    void TransformUtils::ApplyTranslation(const glm::vec3& position, glm::mat4& matModelOut)
    {
        // Translation
        glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f), position);

        matModelOut = matModelOut * matTranslate;
    }

    void TransformUtils::ApplyRotation(const glm::quat& orientation, glm::mat4& matModelOut)
    {
        // Rotation matrix generation
        glm::mat4 matRotation = glm::mat4(orientation);

        matModelOut = matModelOut * matRotation;
    }

    void TransformUtils::ApplyScale(const float& scale, glm::mat4& matModelOut)
    {
        // Scaling matrix
        glm::mat4 matScale = glm::scale(glm::mat4(1.0f), glm::vec3(scale));

        matModelOut = matModelOut * matScale;
    }

    void TransformUtils::GetTransform(const glm::vec3& position,
                                      const glm::quat& orientation,
                                      const float& scale, 
                                      glm::mat4& matModelOut)
    {
        // Combine all the transformations
        ApplyTranslation(position, matModelOut);
        ApplyRotation(orientation, matModelOut);
        ApplyScale(scale, matModelOut);

        return;
    }

    void TransformUtils::GetTransform(const glm::vec3& position, 
                                      const float& scale, 
                                      glm::mat4& matModelOut)
    {
        // Transformation without rotation
        ApplyTranslation(position, matModelOut);
        ApplyScale(scale, matModelOut);

        return;
    }

    glm::vec3 TransformUtils::GetUpVector(const glm::quat& orientation)
    {
        return orientation * UP_VECTOR;
    }

    glm::vec3 TransformUtils::GetForwardVector(const glm::quat& orientation)
    {
        return orientation * FORWARD_VECTOR;
    }

    glm::vec3 TransformUtils::GetRightVector(const glm::quat& orientation)
    {
        return orientation * RIGHT_VECTOR;
    }

    glm::quat TransformUtils::AdjustOrientation(const glm::quat& orientation, 
										        const glm::vec3& delta)
    {
        // To combine quaternion values, you multiply them together
        // Make a quaternion that represents that CHANGE in angle
        glm::quat qChange = GetDegreesAsQuat(delta);

        // Multiply them together to get the change
        // Just like with matrix math
        glm::quat adjustedOrientation = orientation * qChange;

        return adjustedOrientation;
    }

    glm::vec3 TransformUtils::GetQuatAsDegrees(const glm::quat& orientation)
    {
        return glm::degrees(glm::eulerAngles(orientation));
    }

    glm::quat TransformUtils::GetDegreesAsQuat(const glm::vec3& rotation)
    {
        return glm::quat(glm::radians(rotation));
    }

    glm::vec3 TransformUtils::LocalToWorldPoint(const glm::vec3& point,
                                                const glm::vec3& position, const glm::quat& orientation,
                                                const float& scale, 
                                                glm::mat4& parentMat)
    {
        GetTransform(position, orientation, scale, parentMat);

        glm::vec3 worldPoint = parentMat * glm::vec4(point, 1.0f);

        return worldPoint;
    }

    glm::vec3 TransformUtils::LocalToWorldPoint(const glm::vec3& point,
										        const glm::vec3& position, const float& scale,
                                                glm::mat4& parentMat)
    {
        GetTransform(position, scale, parentMat);

        glm::vec3 worldPoint = parentMat * glm::vec4(point, 1.0f);

        return worldPoint;
    }
}
