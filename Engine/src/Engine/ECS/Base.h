#pragma once

#include "Engine/Core/types.h"
#include <bitset>

namespace MyEngine
{
	// Alias for the component type id
	using ComponentType = uint8_t;
	using ComponentId = uint32_t;

	// Type alias for the entities ids
	using Entity = int32_t;

	// Used to define the size of arrays
	const ComponentType MAX_COMPONENTS = 16;
	const Entity MAX_ENTITIES = 1000;

	// Defines an entity's component composition
	using EntityMask = std::bitset<MAX_COMPONENTS>;

	// For any kind of orientation needed
	enum eDirections
	{
		BACKWARD,
		LEFT,
		RIGHT,
		FORWARD
	};
}
