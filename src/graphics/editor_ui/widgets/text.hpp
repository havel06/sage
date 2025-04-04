#pragma once

#include "../widget.hpp"
#include "utils/string.hpp"
#include "utils/colour.hpp"
#include "row.hpp"
#include <raylib/raylib.h>

namespace Editor_UI::Widgets
{

// FIXME - use formatted text, line wrapping
class Text : public Widget
{
public:
	Text(const String&, const Font& font);
	void draw(const Theme& theme, float dt) override;
	void draw_overlay(const Theme&, float) override {}
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i, bool) override {}
	void handle_character(char) override {}
	void handle_key(int) override {}
private:
	const Font& m_font;
	String m_text;
	Vec2i m_position;
};

}
