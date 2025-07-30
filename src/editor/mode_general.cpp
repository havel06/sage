#include "mode_general.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/relative_pane.hpp"
#include "graphics/editor_ui/factories/input_text.hpp"
#include "graphics/editor_ui/factories/input_number.hpp"
#include "graphics/editor_ui/theme.hpp"

namespace Editor
{

Mode_General::Mode_General()
{
	m_window_width_input_state.set_content("1280");
	m_window_height_input_state.set_content("720");
}

Own_Ptr<Editor_UI::Widget_Factory> Mode_General::build(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	return Relative_Pane::make(true,
		Column::make(Column::Padding::normal)
			->add(Input_Text::make(m_name_input_state, theme.font, "Project name"))
			->add(Input_Number::make(m_window_width_input_state, theme.font, "Window width"))
			->add(Input_Number::make(m_window_height_input_state, theme.font, "Window height"))
			->add(Input_Text::make(m_default_sequence_input_state, theme.font, "Initial sequence"))
			->add(Input_Text::make(m_default_character_input_state, theme.font, "Default character"))
	);
}

}
