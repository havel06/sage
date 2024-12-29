#pragma once

// fwd
struct Color;

struct Colour
{
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 255;

	Color to_ray_color() const;
};
