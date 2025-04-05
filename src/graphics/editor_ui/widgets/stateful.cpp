#include "stateful.hpp"
#include "utils/move.hpp"

namespace Editor_UI::Widgets
{

Stateful::Stateful(Own_Ptr<State>&& state) :
	m_state{move(state)}
{
}

void Stateful::draw(const Theme& theme, float dt)
{
	if (!m_child)
		return;

	m_child->draw(theme, dt);
}

void Stateful::draw_overlay(const Theme& theme, float dt)
{
	if (!m_child)
		return;

	m_child->draw_overlay(theme, dt);
}

void Stateful::update(const Theme& theme)
{
	if (!m_initial_build_done || m_state->is_dirty()) {
		m_child = m_state->build(theme)->make_widget();
		m_initial_build_done = true;
	}

	if (!m_child)
		return;

	m_child->update(theme);
}

Vec2i Stateful::layout(const Theme& theme, Recti bounding_box)
{
	if (!m_child)
		return {0, 0};

	return m_child->layout(theme, bounding_box);
}

void Stateful::handle_mouse(Vec2i pos, bool click)
{
	if (!m_child)
		return;

	m_child->handle_mouse(pos, click);
}

void Stateful::handle_character(char character)
{
	if (!m_child)
		return;

	m_child->handle_character(character);
}

void Stateful::handle_key(int key)
{
	if (!m_child)
		return;

	m_child->handle_key(key);
}

void Stateful::handle_scroll(float amount)
{
	if (!m_child)
		return;

	m_child->handle_scroll(amount);
}

}
