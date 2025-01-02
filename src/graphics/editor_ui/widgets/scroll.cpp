#include "scroll.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "utils/log.hpp"
#include "utils/move.hpp"
#include "utils/minmax.hpp"
#include "raylib/raylib.h"

static const int SCROLLBAR_WIDTH = 4;
static const int SCROLLBAR_GAP = 4;

namespace Editor_UI::Widgets
{

Scroll::Scroll(Own_Ptr<Widget>&& child)
{
	m_child = move(child);
}

void Scroll::draw(float dt)
{
	// Draw child
	BeginScissorMode(
		m_bounding_box.position.x,
		m_bounding_box.position.y,
		m_bounding_box.size.x,
		m_bounding_box.size.y
	);
	m_child->draw(dt);
	EndScissorMode();

	// Draw scrollbar
	const int scrollbar_x = m_bounding_box.position.x + m_bounding_box.size.x - SCROLLBAR_WIDTH;
	const int scrollbar_height = (float)m_bounding_box.size.y / m_child_height * m_bounding_box.size.y;
	const int scrollbar_leeway = m_bounding_box.size.y - scrollbar_height;
	const float scrollbar_progress = (float)m_scroll_amount / (m_child_height - m_bounding_box.size.y);
	const int scrollbar_y = m_bounding_box.position.y + scrollbar_leeway * scrollbar_progress;

	DrawRectangleRounded(
		{(float)scrollbar_x, (float)scrollbar_y, SCROLLBAR_WIDTH, (float)scrollbar_height},
		(float)SCROLLBAR_WIDTH / 2,
		3,
		Theme::PRIMARY.to_ray_color()
	);
}

Vec2i Scroll::layout(Recti bounding_box)
{
	Recti child_bounding_box = bounding_box;
	child_bounding_box.size.x -= (SCROLLBAR_WIDTH + SCROLLBAR_GAP);

	Vec2i child_size = m_child->layout(child_bounding_box);

	m_child_height = child_size.y;
	m_bounding_box.position = bounding_box.position;
	m_bounding_box.size.x = bounding_box.size.x;
	m_bounding_box.size.y = min(bounding_box.size.y, child_size.y);

	// Second layout pass to position the child correctly
	child_bounding_box.position.y -= m_scroll_amount;
	m_child->layout(child_bounding_box);

	return m_bounding_box.size;
}

void Scroll::handle_mouse(Vec2i pos, bool click)
{
	m_child->handle_mouse(pos, click);
	m_hover = m_bounding_box.contains(pos);
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
		m_scroll_amount -= amount * 40;

		// Limit scroll amount
		const int scroll_max = max(m_child_height - m_bounding_box.size.y, 0);
		m_scroll_amount = min(m_scroll_amount, scroll_max);
		m_scroll_amount = max(m_scroll_amount, 0);

	}
}

}
