#include "context.hpp"
#include "raylib/raylib.h"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "utils/rect.hpp"

namespace Editor_UI
{

void Context::draw(float dt)
{
	Vec2i mouse_pos = {
		GetMouseX(),
		GetMouseY()
	};

	const float scroll = GetMouseWheelMove();

	for (auto& pane : m_panes) {
		pane->update();
		pane->layout({{0, 0}, {5000, 5000}});
		pane->handle_mouse(mouse_pos, IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
		pane->handle_scroll(scroll);
		pane->draw(dt);
	}
}

void Context::input_char(char character)
{
	for (auto& pane : m_panes)
		pane->handle_character(character);
}

void Context::input_key(int key)
{
	for (auto& pane : m_panes)
		pane->handle_key(key);
}

Widgets::Pane& Context::add_pane(Recti transform, bool padding)
{
	m_panes.push_back(make_own_ptr<Widgets::Pane>(transform, padding));
	return *m_panes.back();
}

}
