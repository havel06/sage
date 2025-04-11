#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/widgets/input_state.hpp"
#include "utils/string.hpp"
#include "graphics/editor_ui/state.hpp"

class Map_Entities;
class Entity;
namespace Editor_UI {
	class System;
}

class Dev_Tools_Mode_Entity : public Editor_UI::State
{
public:
	Dev_Tools_Mode_Entity(Map_Entities&);
	
	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme&) override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget_Factory> create_search_bar(const Editor_UI::Theme& theme);

	Map_Entities& m_map_entities;

	Editor_UI::Widgets::Input_State m_input_state;
	String m_searched_term = "";

	bool m_dirty = true;
};
