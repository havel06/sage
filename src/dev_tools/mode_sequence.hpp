#pragma once
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
		class Pane;
	}
}

// Sequence edit mode UI
class Dev_Tools_Mode_Sequence : public Editor_UI::View_Model
{
public:
	Dev_Tools_Mode_Sequence(Editor_UI::System&, Sequence_Manager&, const String& resource_root_path);
	void update(); // Call when opened
	Own_Ptr<Editor_UI::Widget> build() override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget> build_list();
	Own_Ptr<Editor_UI::Widget> try_build_sequence_edit();

	Sequence_Manager& m_sequence_manager;
	Editor_UI::System& m_gui;
	String m_resource_root;

	Optional<Resource_Handle<Sequence>> m_selected_sequence;

	bool m_dirty = true;
};
