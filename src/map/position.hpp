#pragma once

#include "utils/optional.hpp"
#include "utils/string.hpp"
#include "utils/vec2.hpp"

// fwd
class Map_Entities;


// Denotes a position on the map.
// If entity_name has a value, the position is equal to the position
// of the entity plus the offset. Otherwise, the offset is absolute.
struct Position
{
	Optional<String> entity_name = {};
	Vec2f offset = {0, 0};

	Vec2f resolve(Map_Entities&) const;
};
