#include "mode_gui.hpp"
#include "mode_gui_open_dialog.hpp"

#include "graphics/editor_ui/factories/stateful.hpp"

namespace Editor
{

Own_Ptr<Editor_UI::Widget_Factory> Mode_GUI::build(const Editor_UI::Theme&)
{
	using namespace Editor_UI::Factories;

	return Stateful::make(make_own_ptr<Mode_GUI_Open_Dialog>());
}

}
