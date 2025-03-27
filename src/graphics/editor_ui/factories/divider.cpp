#include "divider.hpp"
#include "graphics/editor_ui/widgets/divider.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Divider* Divider::make()
{
	return new Divider();
}

Own_Ptr<Widget> Divider::make_widget()
{
	return make_own_ptr<Widgets::Divider>();
}

}
