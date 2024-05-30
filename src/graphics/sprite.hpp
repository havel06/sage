#pragma once

#include "utils/rect.hpp"
#include "utils/string.hpp"
#include "texture.hpp"

class Sprite
{
public:
	Recti texture_clip;

	Sprite(const Sage_Texture&);
	Sprite();

	void draw(Rectf transform) const;
	bool is_null() const;
	const String& get_texture_path() const;
private:
	Sage_Texture m_texture;
};
