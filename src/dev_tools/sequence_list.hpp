#pragma once

#include "graphics/editor_ui/view_model.hpp"
#include "io/resource/resource_handle.hpp"
#include "sequence/sequence.hpp"

// fwd
namespace Editor_UI {
	class System;
}
class Sequence_Manager;
class Dev_Tools_Sequence_Detail;

class Dev_Tools_Sequence_List : public Editor_UI::View_Model
{
public:
	Dev_Tools_Sequence_List(Editor_UI::System& system, Sequence_Manager&, Dev_Tools_Sequence_Detail&, const String& resource_root);

	void rebuild(const String& searched_term);
	Own_Ptr<Editor_UI::Widget> build() override;
	bool is_dirty() const override;
private:
	Editor_UI::System& m_system;
	Sequence_Manager& m_sequence_manager;
	Dev_Tools_Sequence_Detail& m_detail;
	String m_resource_root;

	String m_searched_term = "";

	bool m_dirty = true;
};
