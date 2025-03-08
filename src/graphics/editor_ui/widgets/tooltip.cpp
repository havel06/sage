#include "tooltip.hpp"
#include "raylib/raylib.h"
#include "utils/move.hpp"
#include "utils/minmax.hpp"
#include "../theme.hpp"

namespace Editor_UI::Widgets
{

Tooltip::Tooltip(Own_Ptr<Widget>&& child, const String& text, const Font& font) :
	m_child{move(child)},
	m_text{text},
	m_font{font}
{

}

void Tooltip::draw(const Theme& theme, float dt)
{
	m_child->draw(theme, dt);
}

void Tooltip::draw_overlay(const Theme& theme, float dt)
{
	m_child->draw_overlay(theme, dt);

	if (!m_show)
		return;

	// Calculate size
	Vector2 text_size = MeasureTextEx(m_font, m_text.data(), theme.FONT_SIZE_DEFAULT, 0);

	const int padding = theme.PADDING_SMALL;
	const int width = text_size.x + 2 * padding;
	const int height = text_size.y + 2 * padding;

	// Calculate position
	Vec2i position = m_bounding_box.south();

	// Draw
	const float border_radius = 8;
	const float roundness = border_radius / min(m_bounding_box.size.x, m_bounding_box.size.y);
	DrawRectangleRounded(
		{
			(float)position.x,
			(float)position.y,
			(float)width,
			(float)height,
		},
		roundness,
		4,
		theme.INVERSE_SURFACE.to_ray_color()
	);

	DrawTextEx(
		m_font,
		m_text.data(),
		{
			(float)position.x + padding,
			(float)position.y + padding
		},
		theme.FONT_SIZE_DEFAULT,
		0,
		theme.ON_INVERSE_SURFACE.to_ray_color()
	);
}

Vec2i Tooltip::layout(const Theme& theme, Recti bounding_box)
{
	Vec2i child_size = m_child->layout(theme, bounding_box);

	m_bounding_box.position = bounding_box.position;
	m_bounding_box.size = child_size;

	return child_size;
}

void Tooltip::handle_mouse(Vec2i position, bool click)
{
	m_show = m_bounding_box.contains(position);
	m_child->handle_mouse(position, click);
}

void Tooltip::handle_character(char input)
{
	m_child->handle_character(input);
}

void Tooltip::handle_key(int key)
{
	m_child->handle_key(key);
}

void Tooltip::handle_scroll(float amount)
{
	m_child->handle_scroll(amount);
}

}
