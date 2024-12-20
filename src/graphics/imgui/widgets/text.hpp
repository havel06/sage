#pragma once

#include "../widget.hpp"
#include "utils/string.hpp"
#include "utils/colour.hpp"
#include "row.hpp"
#include <raylib/raylib.h>

namespace IMGUI::Widgets
{

// FIXME - use formatted text, line wrapping
class Text : public Widget
{
public:
	Text(const String&, const Font& font, Colour colour);
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
private:
	const Font& m_font;
	String m_text;
	Colour m_colour;
	Vec2i m_position;
};

}