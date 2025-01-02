#pragma once
#include "graphics/editor_ui/context.hpp"
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
class Dev_Tools_Mode_Sequence
{
public:
	Dev_Tools_Mode_Sequence(Editor_UI::System&, Sequence_Manager&, const String& resource_root_path);
	void draw(float dt);
private:
	void rebuild_list();
	void try_rebuild_sequence_edit();

	Sequence_Manager& m_sequence_manager;
	Editor_UI::System& m_gui;
	String m_resource_root;

	Optional<Resource_Handle<Sequence>> m_selected_sequence;

	Editor_UI::Context m_context;
	Editor_UI::Widgets::Pane* m_pane_list;
	Editor_UI::Widgets::Pane* m_pane_detail;
};
