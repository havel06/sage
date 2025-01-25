#include "divider.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "raylib/raylib.h"

namespace Editor_UI::Widgets
{

void Divider::draw(const Theme& theme, float dt)
{
	(void)dt;
	DrawLine(
		m_position.x,
		m_position.y,
		m_position.x + m_width,
		m_position.y,
		Color {
			.r = theme.OUTLINE_VARIANT.r,
			.g = theme.OUTLINE_VARIANT.g,
			.b = theme.OUTLINE_VARIANT.b,
			.a = theme.OUTLINE_VARIANT.a,
		}
	);
}

Vec2i Divider::layout(const Theme& theme, Recti bounding_box)
{
	(void)theme;
	m_position = bounding_box.position;
	m_width = bounding_box.size.x;
	return {m_width, 1};
}

}
