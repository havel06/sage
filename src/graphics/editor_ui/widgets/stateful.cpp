#include "stateful.hpp"
#include "utils/move.hpp"

namespace Editor_UI::Widgets
{

Stateful::Stateful(Own_Ptr<State>&& state) :
	m_state{move(state)}
{
	m_child = m_state->build()->make_widget();
}

void Stateful::draw(const Theme& theme, float dt)
{
	m_child->draw(theme, dt);
}

void Stateful::draw_overlay(const Theme& theme, float dt)
{
	m_child->draw_overlay(theme, dt);
}

void Stateful::update()
{
	if (m_state->is_dirty())
		m_child = m_state->build()->make_widget();

	m_child->update();
}

Vec2i Stateful::layout(const Theme& theme, Recti bounding_box)
{
	return m_child->layout(theme, bounding_box);
}

void Stateful::handle_mouse(Vec2i pos, bool click)
{
	m_child->handle_mouse(pos, click);
}

void Stateful::handle_character(char character)
{
	m_child->handle_character(character);
}

void Stateful::handle_key(int key)
{
	m_child->handle_key(key);
}

void Stateful::handle_scroll(float amount)
{
	m_child->handle_scroll(amount);
}

}
