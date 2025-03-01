#include "view_model_holder.hpp"
#include "../view_model.hpp"

namespace Editor_UI::Widgets
{

View_Model_Holder::View_Model_Holder(View_Model& view_model) :
	m_view_model{view_model}
{
	m_child = m_view_model.build();
}

void View_Model_Holder::draw(const Theme& theme, float dt)
{
	m_child->draw(theme, dt);
}

void View_Model_Holder::draw_overlay(const Theme& theme, float dt)
{
	m_child->draw_overlay(theme, dt);
}

void View_Model_Holder::update()
{
	if (m_view_model.is_dirty())
		m_child = m_view_model.build();

	m_child->update();
}

Vec2i View_Model_Holder::layout(const Theme& theme, Recti bounding_box)
{
	return m_child->layout(theme, bounding_box);
}

void View_Model_Holder::handle_mouse(Vec2i pos, bool click)
{
	m_child->handle_mouse(pos, click);
}

void View_Model_Holder::handle_character(char character)
{
	m_child->handle_character(character);
}

void View_Model_Holder::handle_key(int key)
{
	m_child->handle_key(key);
}

void View_Model_Holder::handle_scroll(float amount)
{
	m_child->handle_scroll(amount);
}

}
