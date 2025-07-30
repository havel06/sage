#pragma once

#include "graphics/editor_ui/state.hpp"
#include "graphics/editor_ui/widgets/input_state.hpp"

class GUI_Loader;

namespace Editor
{

class Mode_General : public Editor_UI::State
{
public:
	Mode_General();
	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme&) override;
	bool is_dirty() const override { return m_dirty; }
private:
	Editor_UI::Widgets::Input_State m_name_input_state;	
	Editor_UI::Widgets::Input_State m_window_width_input_state;	
	Editor_UI::Widgets::Input_State m_window_height_input_state;
	Editor_UI::Widgets::Input_State m_default_sequence_input_state;
	Editor_UI::Widgets::Input_State m_default_character_input_state;

	bool m_dirty = true;
};

}
