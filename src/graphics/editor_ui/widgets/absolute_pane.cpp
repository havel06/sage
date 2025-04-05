#include "absolute_pane.hpp"
#include "../theme.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"
#include <raylib/raylib.h>

namespace Editor_UI::Widgets
{

Absolute_Pane::Absolute_Pane(Recti transform, bool padding)
{
	this->transform = transform;
	m_padding = padding;
}

void Absolute_Pane::update(const Theme& theme)
{
	column.update(theme);
}

void Absolute_Pane::draw(const Theme& theme, float dt)
{
	DrawRectangle(
		transform.position.x,
		transform.position.y,
		transform.size.x,
		transform.size.y,
		Color {
			.r = theme.SURFACE.r,
			.g = theme.SURFACE.g,
			.b = theme.SURFACE.b,
			.a = theme.SURFACE.a
		}
	);

	column.draw(theme, dt);
}

void Absolute_Pane::draw_overlay(const Theme& theme, float dt)
{
	column.draw_overlay(theme, dt);
}

Vec2i Absolute_Pane::layout(const Theme& theme, Recti bounding_box)
{
	// NOTE - bounding_box is ignored, since panes are positioned absolutely
	(void)bounding_box;

	const int padding = m_padding ? theme.PADDING_DEFAULT : 0;
	const Recti children_bounding_box = {
		.position = {
			transform.position.x + padding,
			transform.position.y + padding,
		},
		.size = {
			transform.size.x - 2 * padding,
			transform.size.y - 2 * padding,
		}
	};

	column.layout(theme, children_bounding_box);
	return transform.size;
}

void Absolute_Pane::handle_mouse(Vec2i position, bool click)
{
	(void)position;
	(void)click;
	column.handle_mouse(position, click);
}

void Absolute_Pane::handle_character(char character)
{
	column.handle_character(character);
}

void Absolute_Pane::handle_key(int key)
{
	column.handle_key(key);
}

void Absolute_Pane::handle_scroll(float amount)
{
	column.handle_scroll(amount);
}

}
