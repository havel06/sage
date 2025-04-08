#pragma once

#include "graphics/editor_ui/state.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/widgets/scroll_state.hpp"
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
	Dev_Tools_Entity_List(Map_Entities&, Dev_Tools_Entity_Detail& detail);

	void set_searched_term(const String& searched_term);
	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme& theme) override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget_Factory> build_item(Entity& entity, const Editor_UI::Theme& theme);

	Dev_Tools_Entity_Detail& m_detail;
	Map_Entities& m_entities;
	Editor_UI::Widgets::Scroll_State m_scroll_state;
	String m_searched_term = "";

	bool m_dirty = false;
};
