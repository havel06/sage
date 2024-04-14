#pragma once

#include "utils/rect.hpp"
#include "raylib/raylib.h"

class Sprite
{
public:
	Recti texture_clip;

	Sprite(const Texture&);
	void draw(Rectf transform);
private:
	Texture m_texture;
};
