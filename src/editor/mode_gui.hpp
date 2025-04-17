#pragma once

#include "graphics/editor_ui/state.hpp"
#include "graphics/game_ui/widget_factory.hpp"

class GUI_Loader;

namespace Editor
{

class Mode_GUI : public Editor_UI::State
{
public:
	Mode_GUI(GUI_Loader&);
	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme&) override;
	bool is_dirty() const override { return m_dirty; }

	void open_widget(const String& relative_path);
private:
	Own_Ptr<Editor_UI::Widget_Factory> build_editor(const Editor_UI::Theme&);

	GUI_Loader& m_gui_loader;

	Own_Ptr<Game_UI::Widget_Factory> m_widget = {};
	bool m_dirty = true;
};

}
