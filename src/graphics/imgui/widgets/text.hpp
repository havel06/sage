#pragma once

#include "../widget.hpp"
#include "utils/string.hpp"
#include "utils/colour.hpp"
#include "row.hpp"

namespace IMGUI::Widgets
{

// FIXME - use formatted text, line wrapping
class Text : public Widget
{
public:
	Text(const String&, Colour colour);
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
private:
	String m_text;
	Colour m_colour;
	Vec2i m_position;
};

}
