#include "dialog.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "raylib/raylib.h"
#include "utils/minmax.hpp"


namespace Editor_UI::Widgets
{

Dialog::Dialog(Vec2i size)
{
	m_size = size;
}

void Dialog::update()
{
}

void Dialog::draw(const Theme& theme, float dt)
{
	(void)theme;
	(void)dt;
}

void Dialog::draw_overlay(const Theme& theme, float dt)
{
	const float border_radius = 24;
	const float roundness = border_radius / min(m_size.x, m_size.y);

	DrawRectangleRounded(
		Rectangle{
			(float)m_position.x,
			(float)m_position.y,
			(float)m_size.x,
			(float)m_size.y,
		},
		roundness,
		6,
		theme.SURFACE_CONTAINER_HIGHEST.to_ray_color()
	);

	column.draw(theme, dt);
	column.draw_overlay(theme, dt);
}

Vec2i Dialog::layout(const Theme& theme, Recti bounding_box)
{
	(void)bounding_box;

	// Calculate position
	const int x = (GetScreenWidth() - m_size.x) / 2;
	const int y = (GetScreenHeight() - m_size.y) / 2;

	m_position = {x, y};

	const int padding = theme.PADDING_DEFAULT;
	const Recti children_bounding_box = {
		.position = {
			m_position.x + padding,
			m_position.y + padding,
		},
		.size = {
			m_size.x - 2 * padding,
			m_size.y - 2 * padding,
		}
	};

	column.layout(theme, children_bounding_box);

	return {0, 0}; // Returns 0, so it doesn't mess with containers
}

void Dialog::handle_mouse(Vec2i position, bool click)
{
	column.handle_mouse(position, click);
}

void Dialog::handle_character(char character)
{
	column.handle_character(character);
}

void Dialog::handle_key(int key)
{
	column.handle_key(key);
}

void Dialog::handle_scroll(float amount)
{
	column.handle_scroll(amount);
}

}
