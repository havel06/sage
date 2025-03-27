#include "scroll.hpp"
#include "graphics/editor_ui/widgets/scroll.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Own_Ptr<Scroll> Scroll::make(Own_Ptr<Widget_Factory2>&& child)
{
	return make_own_ptr<Scroll>(move(child));
}

Scroll::Scroll(Own_Ptr<Widget_Factory2>&& child) :
	m_child{move(child)}
{
}

Own_Ptr<Widget> Scroll::make_widget()
{
	auto scroll = make_own_ptr<Widgets::Scroll>(m_child->make_widget());
	scroll->max_height = 99999;
	return scroll;
}

}
