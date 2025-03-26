#include "relative_pane.hpp"
#include "graphics/editor_ui/widgets/relative_pane.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Relative_Pane::Relative_Pane(bool padding, Own_Ptr<Widget_Factory2>&& child) :
	m_padding{padding},
	m_child{move(child)}
{
}

Own_Ptr<Widget> Relative_Pane::make_widget()
{
	auto pane = make_own_ptr<Widgets::Relative_Pane>(m_padding);
	pane->column.add_child(m_child->make_widget());
	return pane;
}

}
