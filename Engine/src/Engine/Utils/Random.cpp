#include "pch.h"
#include "Random.h"

namespace MyEngine
{
    uint32_t Random::PCG_Hash(uint32_t input)
    {
        uint32_t state = input * 747796405u + 2891336453u;
        uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
        return (word >> 22u) ^ word;
    }

    float Random::Float(uint32_t& seed)
    {
        seed = PCG_Hash(seed);
        return (float)seed / (float)UINT32_MAX;
    }

    glm::vec3 Random::Vec3(uint32_t& seed, float min, float max)
    {
        return glm::vec3(
            Float(seed) * (max - min) + min,
            Float(seed) * (max - min) + min,
            Float(seed) * (max - min) + min
        );
    }
}
