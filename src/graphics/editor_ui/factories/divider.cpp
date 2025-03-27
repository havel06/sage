#include "divider.hpp"
#include "graphics/editor_ui/widgets/divider.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Own_Ptr<Divider> Divider::make()
{
	return make_own_ptr<Divider>();
}

Own_Ptr<Widget> Divider::make_widget()
{
	return make_own_ptr<Widgets::Divider>();
}

}
