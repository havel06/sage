#pragma once

#include "graphics/editor_ui/state.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widgets/scroll_state.hpp"
#include "io/resource/resource_handle.hpp"
#include "sequence/sequence.hpp"

// fwd
namespace Editor_UI {
	class System;
}
class Sequence_Manager;
class Dev_Tools_Sequence_Detail;

class Dev_Tools_Sequence_List : public Editor_UI::State
{
public:
	Dev_Tools_Sequence_List(Sequence_Manager&, Dev_Tools_Sequence_Detail&, const String& resource_root, const String& searched_term);

	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme& theme) override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget_Factory> build_item(const String& path, Sequence&, const Editor_UI::Theme& theme);

	Sequence_Manager& m_sequence_manager;
	Dev_Tools_Sequence_Detail& m_detail;
	String m_resource_root;

	String m_searched_term = "";
	Editor_UI::Widgets::Scroll_State m_scroll_state;

	bool m_dirty = true;
};
