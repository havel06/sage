#include "box.hpp"
#include "../widgets/box.hpp"

namespace Game_UI {

Box_Factory::Box_Factory()
{
	register_parameter("colour", m_colour);
}

Own_Ptr<Widget> Box_Factory::make_widget()
{
	// FIXME - layout, children
	Own_Ptr<Box> widget = make_own_ptr<Box>(Layout{});
	widget->colour = m_colour.value;
	return widget;
}

}
