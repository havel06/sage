#pragma once

#include "dev_tools/entity_detail.hpp"
#include "dev_tools/entity_list.hpp"
#include "utils/string.hpp"
#include "graphics/editor_ui/view_model.hpp"

class Map_Entities;
class Entity;
namespace Editor_UI {
	class System;
}

class Dev_Tools_Mode_Entity : public Editor_UI::View_Model
{
public:
	Dev_Tools_Mode_Entity(Editor_UI::System&);
	
	void rebuild(Map_Entities&); // Call when opened

	Own_Ptr<Editor_UI::Widget> build() override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget> create_search_bar();

	Editor_UI::System& m_gui;
	Dev_Tools_Entity_Detail m_detail;
	Dev_Tools_Entity_List m_list;
	Map_Entities* m_map_entities = nullptr;

	bool m_dirty = true;
};
