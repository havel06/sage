#pragma once

#include "graphics/editor_ui/view_model.hpp"
#include "io/resource/resource_handle.hpp"
#include "map/map.hpp"
#include "sequence/sequence.hpp"

// fwd
namespace Editor_UI {
	class System;
}
class Sequence_Manager;
class Dev_Tools_Entity_Detail;

class Dev_Tools_Entity_List : public Editor_UI::View_Model
{
public:
	Dev_Tools_Entity_List(Dev_Tools_Entity_Detail& detail, Editor_UI::System& system);

	void rebuild(Map_Entities&, const String& searched_term);
	Own_Ptr<Editor_UI::Widget> build() override;
	bool is_dirty() const override;
private:
	Dev_Tools_Entity_Detail& m_detail;
	Editor_UI::System& m_system;

	Map_Entities* m_entities = nullptr;
	String m_searched_term = "";

	bool m_dirty = false;
};
