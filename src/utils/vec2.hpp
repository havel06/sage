#pragma once

#include "abs.hpp"
#include <math.h>

template<typename T>
struct Vec2
{
	T x = 0;
	T y = 0;

	template<typename T2>
	operator Vec2<T2>() const
	{
		return {static_cast<T2>(x), static_cast<T2>(y)};
	}

	Vec2<T> abs() const
	{
		return {::abs(x), ::abs(y)};
	}

	Vec2<T> round() const
	{
		return {::round(x), ::round(y)};
	}

	T manhattan() const
	{
		return ::abs(x) + ::abs(y);
	}

	T area() const
	{
		return ::abs(x * y);
	}

	float length() const
	{
		return sqrt(x * x + y * y);
	}

	Vec2<T> normalised() const
	{
		Vec2<T> res;

		if (x != 0)
			res.x = x / ::abs(x);

		if (y != 0)
			res.y = y / ::abs(y);

		return res;
	}

	bool directly_next_to(Vec2<T> other)
	{
		Vec2<T> diff = *this - other;
		return diff.manhattan() == 1;
	}
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;

template<typename T, typename T2>
inline bool operator==(const Vec2<T>& lhs, const Vec2<T2>& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

template<typename T, typename T2>
inline Vec2<T>& operator+=(Vec2<T>& lhs, const Vec2<T2>& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

template<typename T>
inline Vec2<T>& operator-=(Vec2<T>& lhs, const Vec2<T>& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

template<typename T, typename T2>
inline auto operator+(const Vec2<T>& lhs, const Vec2<T2>& rhs) -> Vec2<decltype(lhs.x + rhs.x)>
{
	return {lhs.x + rhs.x, lhs.y + rhs.y};
}

template<typename T, typename T2>
inline auto operator-(const Vec2<T>& lhs, const Vec2<T2>& rhs) -> Vec2<decltype(lhs.x - rhs.x)>
{
	return {lhs.x - rhs.x, lhs.y - rhs.y};
}

template<typename T, typename S>
inline auto operator/(const Vec2<T>& lhs, S rhs) -> Vec2<decltype(lhs.x / rhs)>
{
	return {lhs.x / rhs, lhs.y / rhs};
}

template<typename T, typename S>
inline auto operator*(const Vec2<T>& lhs, S rhs) -> Vec2<decltype(lhs.x / rhs)>
{
	return {lhs.x * rhs, lhs.y * rhs};
}

