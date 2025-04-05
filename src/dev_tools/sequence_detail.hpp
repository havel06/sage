#pragma once

#include "graphics/editor_ui/state.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "io/resource/resource_handle.hpp"
#include "sequence/sequence.hpp"

// fwd
namespace Editor_UI {
	class System;
}

class Dev_Tools_Sequence_Detail : public Editor_UI::State
{
public:
	Dev_Tools_Sequence_Detail(const String& resource_root);

	void set_sequence(Resource_Handle<Sequence>);
	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme& theme) override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget_Factory> build_active_inidicator(const Editor_UI::Theme& theme);
	Own_Ptr<Editor_UI::Widget_Factory> build_progress_bar();
	Own_Ptr<Editor_UI::Widget_Factory> build_reset_button(const Editor_UI::Theme& theme);
	Own_Ptr<Editor_UI::Widget_Factory> build_activate_button(const Editor_UI::Theme& theme);

	Optional<Resource_Handle<Sequence>> m_sequence = {};
	String m_resource_root;
	bool m_dirty = false;
};
