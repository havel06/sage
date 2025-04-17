#include "mode_gui_open_dialog.hpp"

#include "graphics/editor_ui/factories/dialog.hpp"
#include "graphics/editor_ui/factories/text.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/button.hpp"
#include "graphics/editor_ui/factories/input_text.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "utils/log.hpp"
#include "mode_gui.hpp"

namespace Editor
{

Mode_GUI_Open_Dialog::Mode_GUI_Open_Dialog(Mode_GUI& parent) :
	m_parent{parent}
{
}

Own_Ptr<Editor_UI::Widget_Factory> Mode_GUI_Open_Dialog::build(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	return Dialog::make(Vec2i{400, 300},
		Column::make(Column::Padding::normal)
			->add(Text::make(theme.font, "Open widget:"))
			->add(Input_Text::make(m_input_state, theme.font, "File name"))
			->add(build_button(theme))
	);
}

Own_Ptr<Editor_UI::Widget_Factory> Mode_GUI_Open_Dialog::build_button(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	auto callback = [this](){
		m_parent.open_widget(m_input_state.get_content());
	};

	return Button::make(callback)
		->with_text(theme.font, "Open widget");
}

}
