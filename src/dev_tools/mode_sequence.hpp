#pragma once
#include "dev_tools/sequence_list.hpp"
#include "sequence_detail.hpp"
#include "graphics/editor_ui/context.hpp"
#include "graphics/editor_ui/view_model.hpp"
#include "io/resource/resource_handle.hpp"
#include "utils/string.hpp"
#include "utils/optional.hpp"

// fwd
class Sequence_Manager;
class Sequence;
namespace Editor_UI {
	class System;
	namespace Widgets {
		class Absolute_Pane;
	}
}

// Sequence edit mode UI
class Dev_Tools_Mode_Sequence : public Editor_UI::View_Model
{
public:
	Dev_Tools_Mode_Sequence(Editor_UI::System&, Sequence_Manager&, const String& resource_root_path);
	void rebuild(); // Call when opened
	Own_Ptr<Editor_UI::Widget> build() override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget> create_search_bar();

	Editor_UI::System& m_gui;
	String m_resource_root;
	Dev_Tools_Sequence_Detail m_detail;
	Dev_Tools_Sequence_List m_list;

	bool m_dirty = true;
};
