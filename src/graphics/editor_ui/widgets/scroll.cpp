#include "scroll.hpp"
#include "utils/log.hpp"
#include "utils/move.hpp"
#include "utils/minmax.hpp"
#include "raylib/raylib.h"

namespace Editor_UI::Widgets
{

Scroll::Scroll(Own_Ptr<Widget>&& child)
{
	m_child = move(child);
}

void Scroll::draw(float dt)
{
	BeginScissorMode(
		m_bounding_box.position.x,
		m_bounding_box.position.y,
		m_bounding_box.size.x,
		m_bounding_box.size.y
	);

	m_child->draw(dt);

	EndScissorMode();
}

Vec2i Scroll::layout(Recti bounding_box)
{
	Vec2i child_size = m_child->layout(bounding_box);

	m_bounding_box.position = bounding_box.position;
	m_bounding_box.size.x = bounding_box.size.x;
	m_bounding_box.size.y = min(bounding_box.size.y, child_size.y);

	// Limit scroll amount
	const int scroll_max = max(child_size.y - m_bounding_box.size.y, 0);
	m_scroll_amount = min(m_scroll_amount, scroll_max);
	m_scroll_amount = max(m_scroll_amount, 0);

	// Second layout pass to position the child correctly
	m_child->layout(
		Recti {
			{bounding_box.position.x, bounding_box.position.y - m_scroll_amount},
			bounding_box.size
		}
	);

	return m_bounding_box.size;
}

void Scroll::handle_mouse(Vec2i pos, bool click)
{
	m_child->handle_mouse(pos, click);
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
	m_scroll_amount -= amount * 20;
}

}
