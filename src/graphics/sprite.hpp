#pragma once

#include "utils/log.hpp"
#include "utils/rect.hpp"
#include "raylib/raylib.h"

class Sprite
{
public:
	Recti texture_clip;

	Sprite(const Texture&);
	Sprite();

	void draw(Rectf transform) const;
private:
	Texture m_texture;
};
