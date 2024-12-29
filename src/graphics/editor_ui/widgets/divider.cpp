#include "divider.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "raylib/raylib.h"

namespace Editor_UI::Widgets
{

void Divider::draw(float dt)
{
	(void)dt;
	DrawLine(
		m_position.x,
		m_position.y,
		m_position.x + m_width,
		m_position.y,
		Color {
			.r = Theme::OUTLINE_VARIANT.r,
			.g = Theme::OUTLINE_VARIANT.g,
			.b = Theme::OUTLINE_VARIANT.b,
			.a = Theme::OUTLINE_VARIANT.a,
		}
	);
}

Vec2i Divider::layout(Recti bounding_box)
{
	m_position = bounding_box.position;
	m_width = bounding_box.size.x;
	return {m_width, 1};
}

}
