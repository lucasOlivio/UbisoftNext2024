#pragma once

namespace MyEngine
{
	class Random
	{
	public:
		Random() {};
		~Random() {};

		// Fast random unsigned int generator
		// Ref: https://www.youtube.com/watch?v=5_RAHZQCPjE
		static uint32_t PCG_Hash(uint32_t input);

		// Uses PCG hash to generate a random float between 0 and 1
		static float Float(uint32_t& seed);

		// Uses Float to generate random x,y,z values between min and max
		static glm::vec3 Vec3(uint32_t& seed, float min, float max);
	};
}
