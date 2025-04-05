#include "block.hpp"
#include "utils/move.hpp"
#include "utils/minmax.hpp"

namespace Editor_UI::Widgets
{

Block::Block(Own_Ptr<Widget>&& widget, Vec2i max_size)
{
	m_child = move(widget);
	m_max_size = max_size;
}

void Block::draw(const Theme& theme, float dt)
{
	m_child->draw(theme, dt);
}

void Block::draw_overlay(const Theme& theme, float dt)
{
	m_child->draw_overlay(theme, dt);
}

void Block::update(const Theme& theme)
{
	m_child->update(theme);
}

Vec2i Block::layout(const Theme& theme, Recti bounding_box)
{
	Recti transform;
	transform.position = bounding_box.position;
	transform.size.x = min(bounding_box.size.x, m_max_size.x);
	transform.size.y = min(bounding_box.size.y, m_max_size.y);

	m_child->layout(theme, transform);
	return transform.size;
}

void Block::handle_mouse(Vec2i pos, bool click)
{
	m_child->handle_mouse(pos, click);
}

void Block::handle_character(char character)
{
	m_child->handle_character(character);
}

void Block::handle_key(int key)
{
	m_child->handle_key(key);
}

void Block::handle_scroll(float amount)
{
	m_child->handle_scroll(amount);
}

}
