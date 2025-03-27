#include "dummy.hpp"
#include "graphics/editor_ui/widgets/dummy.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Dummy* Dummy::make()
{
	return new Dummy();
}

Own_Ptr<Widget> Dummy::make_widget()
{
	return make_own_ptr<Widgets::Dummy>();
}

}
