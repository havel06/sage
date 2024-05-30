#pragma once

#include "vec2.hpp"
#include <assert.h>

enum class Direction {
	up,
	down,
	right,
	left
};

template<typename T>
Vec2<T> direction_to_vec2(Direction dir)
{
	switch (dir) {
		case Direction::up:
			return {0, -1};
		case Direction::down:
			return {0, 1};
		case Direction::right:
			return {1, 0};
		case Direction::left:
			return {-1, 0};
	}
}

template<typename T>
Direction vec2_to_direction(Vec2<T> vec)
{
	if (vec.y < 0) {
		return Direction::up;
	} else if (vec.y > 0) {
		return Direction::down;
	} else if (vec.x < 0) {
		return Direction::left;
	} else if (vec.x > 0) {
		return Direction::right;
	} else {
		assert(false);
	}
}

inline const char* direction_to_string(Direction dir)
{
	switch (dir) {
		case Direction::up:
			return "up";
		case Direction::down:
			return "down";
		case Direction::right:
			return "right";
		case Direction::left:
			return "left";
	}
}

const auto direction_to_vec2i = direction_to_vec2<int>;
const auto direction_to_vec2f = direction_to_vec2<float>;
const auto vec2i_to_direction = vec2_to_direction<int>;
const auto vec2f_to_direction = vec2_to_direction<float>;
