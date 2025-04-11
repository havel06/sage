#pragma once

#include "graphics/editor_ui/state.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/widgets/input_state.hpp"

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
	void set_entity(Entity*);
	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme& theme) override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget_Factory> make_input_x(const Editor_UI::Theme& theme);
	Own_Ptr<Editor_UI::Widget_Factory> make_input_y(const Editor_UI::Theme& theme);
	Own_Ptr<Editor_UI::Widget_Factory> make_input_speed(const Editor_UI::Theme& theme);

	Editor_UI::Widgets::Input_State m_state_x;
	Editor_UI::Widgets::Input_State m_state_y;
	Editor_UI::Widgets::Input_State m_state_speed;

	Entity* m_current_entity = nullptr;

	bool m_dirty = false;
};
