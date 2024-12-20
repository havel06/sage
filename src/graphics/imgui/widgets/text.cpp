#include "text.hpp"
#include "graphics/imgui/theme.hpp"
#include "raylib/raylib.h"
#include "utils/colour.hpp"

namespace IMGUI::Widgets
{

Text::Text(const String& str, const Font& font, Colour colour) :
	m_font{font}
{
	m_text = str;
	m_colour = colour;
}

void Text::draw()
{
	DrawTextEx(
		m_font,
		m_text.data(),
		Vector2{
			(float)m_position.x,
			(float)m_position.y,
		},
		Theme::FONT_SIZE_DEFAULT,
		0,
		Color {
			m_colour.r,	
			m_colour.g,	
			m_colour.b,	
			m_colour.a,	
		}
	);
}

Vec2i Text::layout(Recti bounding_box)
{
	m_position = bounding_box.position;

	const int width = MeasureText(m_text.data(), Theme::FONT_SIZE_DEFAULT);
	const int height = Theme::FONT_SIZE_DEFAULT;

	return Vec2i{width, height};
}

}
