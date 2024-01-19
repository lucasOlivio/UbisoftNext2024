#pragma once

namespace MyEngine
{
    void WrapMinMax(int min, int max, int& numOut);

    void WrapMinMax(float min, float max, float& numOut);

    // From: Real-Time Collision Detection- Ericson, Christer- 9781558607323- Books - Amazon.ca
    // Chapter 5:
    glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);

    glm::vec3 ReplaceNaNWithValue(const glm::vec3& vecIn, const float& value);
}
