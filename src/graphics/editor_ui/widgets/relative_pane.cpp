#include "relative_pane.hpp"
#include "../theme.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"
#include <raylib/raylib.h>

namespace Editor_UI::Widgets
{

Relative_Pane::Relative_Pane(bool padding)
{
	m_padding = padding;
}

void Relative_Pane::update()
{
	column.update();
}

void Relative_Pane::draw(const Theme& theme, float dt)
{
	DrawRectangle(
		m_transform.position.x,
		m_transform.position.y,
		m_transform.size.x,
		m_transform.size.y,
		Color {
			.r = theme.SURFACE.r,
			.g = theme.SURFACE.g,
			.b = theme.SURFACE.b,
			.a = theme.SURFACE.a
		}
	);

	column.draw(theme, dt);
}

Vec2i Relative_Pane::layout(const Theme& theme, Recti bounding_box)
{
	m_transform = bounding_box;

	const int padding = m_padding ? theme.PADDING_DEFAULT : 0;
	const Recti children_bounding_box = {
		.position = {
			m_transform.position.x + padding,
			m_transform.position.y + padding,
		},
		.size = {
			m_transform.size.x - 2 * padding,
			m_transform.size.y - 2 * padding,
		}
	};

	column.layout(theme, children_bounding_box);
	return m_transform.size;
}

void Relative_Pane::handle_mouse(Vec2i position, bool click)
{
	column.handle_mouse(position, click);
}

void Relative_Pane::handle_character(char character)
{
	column.handle_character(character);
}

void Relative_Pane::handle_key(int key)
{
	column.handle_key(key);
}

void Relative_Pane::handle_scroll(float amount)
{
	column.handle_scroll(amount);
}

}
