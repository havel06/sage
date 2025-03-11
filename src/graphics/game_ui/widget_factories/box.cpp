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
	return make_own_ptr<Box>(Layout{});
}

}
