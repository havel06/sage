#pragma once

#include "graphics/editor_ui/view_model.hpp"
#include "io/resource/resource_handle.hpp"
#include "sequence/sequence.hpp"

// fwd
namespace Editor_UI {
	class System;
}

class Dev_Tools_Sequence_Detail : public Editor_UI::View_Model
{
public:
	Dev_Tools_Sequence_Detail(Editor_UI::System& system, const String& resource_root);

	void set_sequence(Resource_Handle<Sequence>);
	Own_Ptr<Editor_UI::Widget> build() override;
	bool is_dirty() const override;
private:
	Editor_UI::System& m_system;
	Optional<Resource_Handle<Sequence>> m_sequence = {};
	String m_resource_root;
	bool m_dirty = false;
};
