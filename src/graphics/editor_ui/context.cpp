#include "context.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "raylib/raylib.h"
#include "theme.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "utils/rect.hpp"
#include "utils/move.hpp"

namespace Editor_UI
{

Context::Context(const Theme& theme) : m_theme{theme}
{
}

void Context::draw(float dt)
{
	if (!m_top_widget)
		return;

	Vec2i mouse_pos = {
		GetMouseX(),
		GetMouseY()
	};

	const float scroll = GetMouseWheelMove();

	m_top_widget->update(m_theme);
	m_top_widget->layout(m_theme, {{0, 0}, {GetScreenWidth(), GetScreenHeight()}});
	m_top_widget->handle_mouse(mouse_pos, IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
	m_top_widget->handle_scroll(scroll);
	m_top_widget->draw(m_theme, dt);
	m_top_widget->draw_overlay(m_theme, dt);
}

void Context::input_char(char character)
{
	if (!m_top_widget)
		return;

	m_top_widget->handle_character(character);
}

void Context::input_key(int key)
{
	if (!m_top_widget)
		return;

	m_top_widget->handle_key(key);
}

void Context::set_top_widget(Own_Ptr<Widget_Factory>&& widget)
{
	m_top_widget = widget->make_widget();
}

}
