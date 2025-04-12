#include "main_widget.hpp"

#include "graphics/editor_ui/factories/stateful.hpp"
#include "mode_gui.hpp"

namespace Editor
{

Own_Ptr<Editor_UI::Widget_Factory> Main_Widget::build(const Editor_UI::Theme&)
{
	using namespace Editor_UI::Factories;

	return Stateful::make(make_own_ptr<Mode_GUI>());
}

}
