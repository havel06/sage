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
	void draw(const Theme& theme, float dt) override;
	void draw_overlay(const Theme&, float) override {}
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i, bool) override {}
	void handle_character(char) override {}
	void handle_key(int) override {}
private:
	Sprite m_sprite;
	Vec2i m_size;
	Vec2i m_position; // Calculated by layout
};

}
