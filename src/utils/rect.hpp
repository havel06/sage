#pragma once

#include "vec2.hpp"

template<typename T>
struct Rect
{
	Vec2<T> position;
	Vec2<T> size;

	template<typename T2>
	operator Rect<T2>() const
	{
		return {static_cast<Vec2<T2>>(position), static_cast<Vec2<T2>>(size)};
	}

	bool contains(Vec2<T> vector) const
	{
		return vector.x >= position.x && vector.y >= position.y && (vector.x - position.x) < size.x && (vector.y - position.y) < size.y;
	}

	bool overlaps(Rect<T> other) const
	{
		//one is to the left of the other
		if (position.x + size.x < other.position.x || other.position.x + other.size.x < position.x) {
			return false;
		}
		//one is above the other
		if (position.y + size.y < other.position.y || other.position.y + other.size.y < position.y) {
			return false;
		}
		return true;
	}

	Rect<T> scale_from_center(float scale)
	{
		const Vec2<T> offset = size * (scale - 1) / 2;

		return Rect<T>{
			.position = position - offset,
			.size = size * scale
		};
	}

	Vec2<T> south()
	{
		return Vec2<T> {
			.x = position.x + size.x / 2,
			.y = position.y + size.y
		};
	}

	// FIXME - north, west, east
};

using Recti = Rect<int>;
using Rectf = Rect<float>;

