#pragma once
#include "dev_tools/sequence_list.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "sequence_detail.hpp"
#include "graphics/editor_ui/context.hpp"
#include "graphics/editor_ui/state.hpp"
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
class Dev_Tools_Mode_Sequence : public Editor_UI::State
{
public:
	Dev_Tools_Mode_Sequence(Sequence_Manager&, const String& resource_root_path);
	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme& theme) override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget_Factory> create_search_bar(Dev_Tools_Sequence_List& list, const Editor_UI::Theme& theme);

	String m_resource_root;
	Sequence_Manager& m_seq_manager;

	bool m_dirty = true;
};
