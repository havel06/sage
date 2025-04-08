#include "scroll.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "utils/log.hpp"
#include "utils/move.hpp"
#include "utils/minmax.hpp"
#include "raylib/raylib.h"

static const int SCROLLBAR_WIDTH = 8;
static const int SCROLLBAR_GAP = 6;

namespace Editor_UI::Widgets
{

Scroll::Scroll(Scroll_State& state, Own_Ptr<Widget>&& child) :
	m_state{state}
{
	m_child = move(child);
}

void Scroll::update(const Theme& theme)
{
	m_child->update(theme);
}

void Scroll::draw(const Theme& theme, float dt)
{
	// Draw child
	BeginScissorMode(
		m_bounding_box.position.x,
		m_bounding_box.position.y,
		m_bounding_box.size.x,
		m_bounding_box.size.y
	);
	m_child->draw(theme, dt);
	EndScissorMode();

	// Draw scrollbar
	Recti scrollbar_transform = get_scrollbar_transform();

	DrawRectangleRounded(
		{
			(float)scrollbar_transform.position.x,
			(float)scrollbar_transform.position.y,
			(float)scrollbar_transform.size.x,
			(float)scrollbar_transform.size.y
		},
		(float)SCROLLBAR_WIDTH / 2,
		8,
		theme.PRIMARY.to_ray_color()
	);
}

void Scroll::draw_overlay(const Theme& theme, float dt)
{
	m_child->draw_overlay(theme, dt);
}

Recti Scroll::get_scrollbar_transform()
{
	const int scrollbar_x = m_bounding_box.position.x + m_bounding_box.size.x - SCROLLBAR_WIDTH;
	const int scrollbar_height = (float)m_bounding_box.size.y / m_child_height * m_bounding_box.size.y;
	const int scrollbar_leeway = m_bounding_box.size.y - scrollbar_height;
	const float scrollbar_progress = (float)m_state.get_offset(m_child_height, m_bounding_box.size.y) / (m_child_height - m_bounding_box.size.y);
	const int scrollbar_y = m_bounding_box.position.y + scrollbar_leeway * scrollbar_progress;

	return Recti{
		.position = Vec2i{
			scrollbar_x, scrollbar_y
		},
		.size = Vec2i{
			SCROLLBAR_WIDTH, scrollbar_height	
		}
	};
}

Vec2i Scroll::layout(const Theme& theme, Recti bounding_box)
{
	Recti child_bounding_box = bounding_box;
	child_bounding_box.size.x -= (SCROLLBAR_WIDTH + SCROLLBAR_GAP);

	Vec2i child_size = m_child->layout(theme, child_bounding_box);

	m_child_height = child_size.y;
	m_bounding_box.position = bounding_box.position;
	m_bounding_box.size.x = bounding_box.size.x;
	m_bounding_box.size.y = min(bounding_box.size.y, child_size.y);
	m_bounding_box.size.y = min(m_bounding_box.size.y, max_height);

	// Second layout pass to position the child correctly
	child_bounding_box.position.y -= m_state.get_offset(m_child_height, m_bounding_box.size.y);
	m_child->layout(theme, child_bounding_box);

	return m_bounding_box.size;
}

void Scroll::handle_mouse(Vec2i pos, bool click)
{
	m_child->handle_mouse(pos, click);
	m_hover = m_bounding_box.contains(pos);

	// Scrollbar mouse move
	if (m_scrollbar_held) {
		int scrollbar_delta_px = pos.y - m_scrollbar_hold_last_y;
		const int scroll_change = scrollbar_delta_px * ((float)m_child_height / m_bounding_box.size.y);
		m_state.update_offset(scroll_change);
	}
	m_scrollbar_hold_last_y = pos.y;

	// Scrollbar hold
	if (!m_scrollbar_held) {
		m_scrollbar_held = get_scrollbar_transform().contains(pos) && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
	} else {
		if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			m_scrollbar_held = false;
		}
	}
}

void Scroll::handle_character(char input)
{
	m_child->handle_character(input);
}

void Scroll::handle_key(int key)
{
	m_child->handle_key(key);
}

void Scroll::handle_scroll(float amount)
{
	if (m_hover) {
		m_state.update_offset(amount * 40);
	}
}

}
