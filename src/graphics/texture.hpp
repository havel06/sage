#pragma once

#include <raylib/raylib.h>
#include "utils/string.hpp"

// TODO - use RAII to automatically free raylib textures?
class Sage_Texture
{
public:
	Texture ray_texture;
	String path;
};
