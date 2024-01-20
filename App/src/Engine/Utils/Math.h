#pragma once

namespace MyEngine
{
	class Math
	{
	public:

		// Returns the sign for the number -1, 0, or 1
		template <typename T> 
		static int Sign(T val) 
		{
			return (T(0) < val) - (val < T(0));
		}

		static float DegreesToRadians(float degrees);
	};
}
