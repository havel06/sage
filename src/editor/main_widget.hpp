#pragma once

#include "graphics/editor_ui/state.hpp"

// fwd
class GUI_Loader;

namespace Editor
{

class Main_Widget : public Editor_UI::State
{
public:
	Main_Widget(GUI_Loader&);
	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme&) override;
	bool is_dirty() const override { return false; }
private:
	GUI_Loader& m_gui_loader;
};

}
