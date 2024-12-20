#include "context.hpp"
#include "utils/own_ptr.hpp"
#include "utils/rect.hpp"

namespace Editor_UI
{

void Context::draw()
{
	for (auto& pane : m_panes) {
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
