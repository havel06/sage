#include "input.hpp"
#include "../theme.hpp"
#include "utils/log.hpp"
#include "utils/minmax.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"
#include <ctype.h>
#include <raylib/raylib.h>

// <math.h> fwd
extern "C"
{
double fmod(double, double);
}

namespace Editor_UI::Widgets
{

bool Input_Constraint_Integer::is_valid(const String& input) const
{
	if (input.empty())
		return false;

	for (int i = 0; i < input.length(); i++) {
		if (!isdigit(input[i]))
			return false;
	}

	return true;
}

bool Input_Constraint_Number::is_valid(const String& input) const
{
	if (input.empty())
		return false;

	{
		char* ptr = nullptr;
		strtof(input.data(), &ptr);

		// Check for valid conversion
		if (ptr != input.data())
			return true;
	}

	return false;
}


Input::Input(const Font& font, const String& label, Input_State& state, Own_Ptr<Input_Constraint>&& constraint) :
	m_constraint{move(constraint)},
	m_state{state},
	m_font{font}
{
	m_label = label;
}

bool Input::is_valid() const
{
	return m_constraint->is_valid(m_state.get_content());
}

void Input::draw(const Theme& theme, float dt)
{
	const int segments = 4;
	const int radius = 4;

	Colour colour_outline = theme.OUTLINE;
	Colour colour_fg = theme.ON_SURFACE;

	if (!is_valid()) {
		colour_outline = theme.ERROR;
		colour_fg = theme.ERROR;
	} else if (m_state.active) {
		colour_outline = theme.PRIMARY;
		colour_fg = theme.PRIMARY;
	}

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
		colour_outline.to_ray_color()
	);

	const int padding_left = 16;
	// Draw label
	if (m_state.active || !m_state.get_content().empty()) {
		const int font_size = 14;
		const int label_pos_y = m_bounding_box.position.y - font_size / 2;
		const int width = MeasureTextEx(m_font, m_label.data(), font_size, 0).x;
		DrawRectangle(
			m_bounding_box.position.x + padding_left - 2, // Extra padding
			m_bounding_box.position.y - font_size / 2,
			width + 4, // Extra padding
			font_size,
			theme.SURFACE.to_ray_color()
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
			colour_fg.to_ray_color()
		);
	} else {
		const int padding_top = (48 - theme.FONT_SIZE_DEFAULT) / 2;
		DrawTextEx(
			m_font,
			m_label.data(),
			Vector2 {
				(float)m_bounding_box.position.x + padding_left,
				(float)m_bounding_box.position.y + padding_top,
			},
			theme.FONT_SIZE_DEFAULT,
			0,
			colour_fg.to_ray_color()
		);
	}

	// Draw content
	// FIXME - duplicate code with label drawing
	const int padding_top = (48 - theme.FONT_SIZE_DEFAULT) / 2;
	DrawTextEx(
		m_font,
		m_state.get_content().data(),
		Vector2 {
			(float)m_bounding_box.position.x + padding_left,
			(float)m_bounding_box.position.y + padding_top,
		},
		theme.FONT_SIZE_DEFAULT,
		0,
		theme.ON_SURFACE.to_ray_color()
	);
	// Draw hint
	if (m_state.get_current_hint().length() > m_state.get_content().length()) {
		const int content_width = MeasureTextEx(m_font, m_state.get_content().data(), theme.FONT_SIZE_DEFAULT, 0).x;
		const String hint_rest = m_state.get_current_hint().substring(m_state.get_content().length(), m_state.get_current_hint().length() - m_state.get_content().length());
		DrawTextEx(
			m_font,
			hint_rest.data(),
			Vector2 {
				(float)m_bounding_box.position.x + padding_left + content_width,
				(float)m_bounding_box.position.y + padding_top,
			},
			theme.FONT_SIZE_DEFAULT,
			0,
			ORANGE
		);
	}

	// Draw cursor
	if (m_state.active && m_time_since_cursor_blink < 0.5) {
		const int content_width =
			m_state.get_content().empty() ?
				0 :
				MeasureTextEx(m_font, m_state.get_content().substring(0, m_state.get_cursor_position()).data(), theme.FONT_SIZE_DEFAULT, 0).x;
		const int cursor_added_height = 3;
		const int cursor_x = m_bounding_box.position.x + padding_left + content_width + 2;
		const int cursor_y = m_bounding_box.position.y + padding_top - cursor_added_height;
		const int cursor_width = 1;
		const int cursor_height = theme.FONT_SIZE_DEFAULT + 2 * cursor_added_height;
		DrawRectangle(cursor_x, cursor_y, cursor_width, cursor_height, theme.ON_SURFACE.to_ray_color());
	}

	m_time_since_cursor_blink = fmod(m_time_since_cursor_blink + dt, 1);
}

Vec2i Input::layout(const Theme& theme, Recti bounding_box)
{
	(void)theme;
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
		m_state.active = hover;
	}
}

void Input::handle_character(char character)
{
	m_state.insert_character(character);

	m_time_since_cursor_blink = 0;
	on_edit();
}

void Input::handle_key(int key)
{
	if (!m_state.active)
		return;

	if (key == KEY_BACKSPACE) {
		if (IsKeyDown(KEY_LEFT_CONTROL)) {
			m_state.delete_last_word();
		} else {
			m_state.delete_character();
		}
		m_time_since_cursor_blink = 0;
		on_edit();
	} else if (key == KEY_ESCAPE) {
		m_state.active = false;
		on_edit();
	} else if (key == KEY_TAB) {
		m_state.use_hint();
	} else if (key == KEY_ENTER) {
		on_enter();
	} else if (key == KEY_LEFT) {
		m_state.move_cursor_left();
		m_time_since_cursor_blink = 0;
	} else if (key == KEY_RIGHT) {
		m_state.move_cursor_right();
		m_time_since_cursor_blink = 0;
	}
}

}
