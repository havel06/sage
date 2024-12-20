#include "context.hpp"
#include "raylib/raylib.h"
#include "utils/own_ptr.hpp"
#include "utils/rect.hpp"

namespace Editor_UI
{

void Context::draw()
{
	Vec2i mouse_pos = {
		GetMouseX(),
		GetMouseY()
	};

	for (auto& pane : m_panes) {
		pane->handle_mouse(mouse_pos, IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
		pane->layout({{0, 0}, {5000, 5000}});
		pane->draw();
	}
}

Widgets::Pane& Context::add_pane(Recti transform, bool padding)
{
	m_panes.push_back(make_own_ptr<Widgets::Pane>(transform, padding));
	return *m_panes.back();
}

}
