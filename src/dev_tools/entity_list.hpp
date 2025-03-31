#pragma once

#include "graphics/editor_ui/state.hpp"
#include "graphics/editor_ui/widget_factory2.hpp"
#include "io/resource/resource_handle.hpp"
#include "map/map.hpp"
#include "sequence/sequence.hpp"

// fwd
namespace Editor_UI {
	class System;
}
class Sequence_Manager;
class Dev_Tools_Entity_Detail;

class Dev_Tools_Entity_List : public Editor_UI::State
{
public:
	Dev_Tools_Entity_List(Map_Entities&, Dev_Tools_Entity_Detail& detail, Editor_UI::System& system);

	void set_searched_term(const String& searched_term);
	Own_Ptr<Editor_UI::Widget_Factory2> build() override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget_Factory2> build_item(Entity& entity);

	Dev_Tools_Entity_Detail& m_detail;
	Editor_UI::System& m_system;

	Map_Entities& m_entities;
	String m_searched_term = "";

	bool m_dirty = false;
};
