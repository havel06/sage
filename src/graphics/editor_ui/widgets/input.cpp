#include "input.hpp"
#include "../theme.hpp"
#include "utils/log.hpp"
#include <raylib/raylib.h>

namespace Editor_UI::Widgets
{

Input::Input(const Font& font, const String& label) :
	m_font{font}
{
	m_label = label;
}

void Input::draw(float dt)
{
	const int segments = 4;
	const int radius = 4;

	// Draw outline
	DrawRectangleRoundedLines(
		Rectangle{
			(float)m_bounding_box.position.x,
			(float)m_bounding_box.position.y,
			(float)m_bounding_box.size.x,
			(float)m_bounding_box.size.y
		},
		radius,
		segments,
		1,
		Theme::OUTLINE.to_ray_color()
	);

	const int padding_left = 16;
	// Draw label
	if (active || !content.empty()) {
		const int font_size = 14;
		const int label_pos_y = m_bounding_box.position.y - font_size / 2;
		const int width = MeasureTextEx(m_font, m_label.data(), font_size, 0).x;
		DrawRectangle(
			m_bounding_box.position.x + padding_left - 2, // Extra padding
			m_bounding_box.position.y - font_size / 2,
			width + 4, // Extra padding
			font_size,
			Theme::SURFACE.to_ray_color()
		);
		DrawTextEx(
			m_font,
			m_label.data(),
			Vector2{
				(float)m_bounding_box.position.x + padding_left,
				(float)label_pos_y,
			},
			font_size,
			0,
			Theme::ON_SURFACE.to_ray_color()
		);
	} else {
		const int padding_top = (48 - Theme::FONT_SIZE_DEFAULT) / 2;
		DrawTextEx(
			m_font,
			m_label.data(),
			Vector2 {
				(float)m_bounding_box.position.x + padding_left,
				(float)m_bounding_box.position.y + padding_top,
			},
			Theme::FONT_SIZE_DEFAULT,
			0,
			Theme::ON_SURFACE.to_ray_color()
		);
	}

	// Draw content
	// FIXME - duplicate code with label drawing
	const int padding_top = (48 - Theme::FONT_SIZE_DEFAULT) / 2;
	DrawTextEx(
		m_font,
		content.data(),
		Vector2 {
			(float)m_bounding_box.position.x + padding_left,
			(float)m_bounding_box.position.y + padding_top,
		},
		Theme::FONT_SIZE_DEFAULT,
		0,
		Theme::ON_SURFACE.to_ray_color()
	);

	// Draw cursor
	if (active && m_time_since_cursor_blink < 0.5) {
		const int content_width = MeasureTextEx(m_font, content.data(), Theme::FONT_SIZE_DEFAULT, 0).x;
		const int cursor_added_height = 3;
		const int cursor_x = m_bounding_box.position.x + padding_left + content_width + 2;
		const int cursor_y = m_bounding_box.position.y + padding_top - cursor_added_height;
		const int cursor_width = 1;
		const int cursor_height = Theme::FONT_SIZE_DEFAULT + 2 * cursor_added_height;
		DrawRectangle(cursor_x, cursor_y, cursor_width, cursor_height, Theme::ON_SURFACE.to_ray_color());
	}

	m_time_since_cursor_blink = fmod(m_time_since_cursor_blink + dt, 1);
}

Vec2i Input::layout(Recti bounding_box)
{
	m_bounding_box = Recti{
		.position = bounding_box.position,
		.size = Vec2i{
			.x = bounding_box.size.x,
			.y = 48
		}
	};

	return m_bounding_box.size;
}

void Input::handle_mouse(Vec2i position, bool click)
{
	const bool hover = m_bounding_box.contains(position);

	if (hover) {
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
	}

	if (click) {
		m_time_since_cursor_blink = 0;
		active = hover;
	}
}

void Input::handle_character(char character)
{
	content.append(character);
	m_time_since_cursor_blink = 0;
}

void Input::handle_key(int key)
{
	if (key == KEY_BACKSPACE) {
		if (IsKeyDown(KEY_LEFT_CONTROL)) {
			content.clear();
		} else {
			content.pop();
		}
	} else if (key == KEY_ESCAPE) {
		active = false;
	}
}

}
