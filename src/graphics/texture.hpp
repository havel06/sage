#pragma once

#include <raylib/raylib.h>
#include "utils/string.hpp"

// TODO - use RAII to automatically free raylib textures?
// FIXME - can we move path to the resource class and remove this class completely? Yes, we can!
class Sage_Texture
{
public:
	Texture ray_texture;
	String path;
};
