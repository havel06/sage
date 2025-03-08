#include "text.hpp"
#include "../theme.hpp"
#include "raylib/raylib.h"
#include "utils/colour.hpp"

namespace Editor_UI::Widgets
{

Text::Text(const String& str, const Font& font) :
	m_font{font}
{
	m_text = str;
}

void Text::draw(const Theme& theme, float dt)
{
	(void)dt;
	DrawTextEx(
		m_font,
		m_text.data(),
		Vector2{
			(float)m_position.x,
			(float)m_position.y,
		},
		theme.FONT_SIZE_DEFAULT,
		0,
		Color {
			theme.ON_SURFACE.r,	
			theme.ON_SURFACE.g,	
			theme.ON_SURFACE.b,	
			theme.ON_SURFACE.a,	
		}
	);
}

Vec2i Text::layout(const Theme& theme, Recti bounding_box)
{
	m_position = bounding_box.position;

	const int width = MeasureTextEx(m_font, m_text.data(), theme.FONT_SIZE_DEFAULT, 0).x;
	const int height = theme.FONT_SIZE_DEFAULT;

	return Vec2i{width, height};
}

}
