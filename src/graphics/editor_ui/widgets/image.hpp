#pragma once

#include "../widget.hpp"
#include "utils/own_ptr.hpp"
#include "graphics/sprite.hpp"

namespace Editor_UI::Widgets
{

class Image : public Widget
{
public:
	Image(const Sprite& sprite, Vec2i size);
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
private:
	Sprite m_sprite;
	Vec2i m_size;
	Vec2i m_position; // Calculated by layout
};

}
