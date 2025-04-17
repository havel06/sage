#pragma once

#include "graphics/editor_ui/state.hpp"
#include "graphics/editor_ui/widgets/input_state.hpp"

namespace Editor
{

class Mode_GUI;

class Mode_GUI_Open_Dialog : public Editor_UI::State
{
public:
	Mode_GUI_Open_Dialog(Mode_GUI&);
	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme&) override;
	bool is_dirty() const override { return false; }
private:
	Own_Ptr<Editor_UI::Widget_Factory> build_button(const Editor_UI::Theme&);

	Mode_GUI& m_parent;
	Editor_UI::Widgets::Input_State m_input_state;
};

}
