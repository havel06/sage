#include "stack.hpp"
#include "utils/move.hpp"

namespace Editor_UI::Widgets
{

void Stack::add_child(Own_Ptr<Widget>&& child)
{
	m_children.push_back(move(child));
}

void Stack::set_current_widget(int index)
{
	if (index < 0)
		index = 0;
	else if (index >= m_children.size())
		index = m_children.size() - 1;

	m_current = index;
}

void Stack::update()
{
	if (m_children.empty())
		return;

	m_children[m_current]->update();
}

void Stack::draw(const Theme& theme, float dt)
{
	if (m_children.empty())
		return;

	m_children[m_current]->draw(theme, dt);
}

Vec2i Stack::layout(const Theme& theme, Recti bounding_box)
{
	(void)theme;
	if (m_children.empty())
		return {0, 0};

	return m_children[m_current]->layout(theme, bounding_box);
}

void Stack::handle_mouse(Vec2i pos, bool click)
{
	if (m_children.empty())
		return;

	m_children[m_current]->handle_mouse(pos, click);

}

void Stack::handle_character(char character)
{
	if (m_children.empty())
		return;

	m_children[m_current]->handle_character(character);
}

void Stack::handle_key(int key)
{
	if (m_children.empty())
		return;

	m_children[m_current]->handle_key(key);
}

void Stack::handle_scroll(float amount)
{
	if (m_children.empty())
		return;

	m_children[m_current]->handle_scroll(amount);
}

}
