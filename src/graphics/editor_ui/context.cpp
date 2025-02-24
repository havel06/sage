#include "context.hpp"
#include "raylib/raylib.h"
#include "theme.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "utils/rect.hpp"
#include "utils/move.hpp"

namespace Editor_UI
{

void Context::draw(float dt)
{
	if (!m_top_widget)
		return;

	Vec2i mouse_pos = {
		GetMouseX(),
		GetMouseY()
	};

	const float scroll = GetMouseWheelMove();

	Theme theme; // Use default theme

	m_top_widget->update();
	m_top_widget->layout(theme, {{0, 0}, {GetScreenWidth(), GetScreenHeight()}});
	m_top_widget->handle_mouse(mouse_pos, IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
	m_top_widget->handle_scroll(scroll);
	m_top_widget->draw(theme, dt);
}

void Context::input_char(char character)
{
	m_top_widget->handle_character(character);
}

void Context::input_key(int key)
{
	m_top_widget->handle_key(key);
}

void Context::set_top_widget(Own_Ptr<Widget>&& widget)
{
	m_top_widget = move(widget);
}

}
