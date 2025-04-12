#include "mode_gui_open_dialog.hpp"

#include "graphics/editor_ui/factories/dialog.hpp"
#include "graphics/editor_ui/factories/text.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "utils/log.hpp"

namespace Editor
{

Own_Ptr<Editor_UI::Widget_Factory> Mode_GUI_Open_Dialog::build(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	return Dialog::make(Vec2i{400, 300},
		Text::make(theme.font, "Open widget:")
	);
}

}
