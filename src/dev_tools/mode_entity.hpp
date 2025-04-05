#pragma once

#include "dev_tools/entity_detail.hpp"
#include "dev_tools/entity_list.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
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
	Own_Ptr<Editor_UI::Widget_Factory> create_search_bar(Dev_Tools_Entity_List& list, const Editor_UI::Theme& theme);

	Map_Entities& m_map_entities;

	bool m_dirty = true;
};
