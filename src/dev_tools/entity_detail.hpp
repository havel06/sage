#pragma once

#include "graphics/editor_ui/state.hpp"
#include "graphics/editor_ui/widget_factory2.hpp"

// fwd
namespace Editor_UI {
	class System;
	namespace Widgets {
		class Input;
	}
}
class Entity;

class Dev_Tools_Entity_Detail : public Editor_UI::State
{
public:
	Dev_Tools_Entity_Detail(Editor_UI::System& system);

	void set_entity(Entity*);
	Own_Ptr<Editor_UI::Widget_Factory2> build() override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget_Factory2> make_input_x();
	Own_Ptr<Editor_UI::Widget_Factory2> make_input_y();
	Own_Ptr<Editor_UI::Widget_Factory2> make_input_speed();

	Editor_UI::System& m_system;
	Entity* m_current_entity = nullptr;

	bool m_dirty = false;
};
