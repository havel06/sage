#pragma once

#include "utils/rect.hpp"

struct Texture; // raylib

class Sprite
{
public:
	Recti texture_clip;

	Sprite(const Texture&);
	void draw(Rectf transform);
private:
	const Texture* m_texture = nullptr;
};
