#pragma once

#include "graphics/editor_ui/view_model.hpp"

// fwd
namespace Editor_UI {
	class System;
}
class Entity;

class Dev_Tools_Entity_Detail : public Editor_UI::View_Model
{
public:
	Dev_Tools_Entity_Detail(Editor_UI::System& system);

	void set_entity(Entity*);
	Own_Ptr<Editor_UI::Widget> build() override;
	bool is_dirty() const override;
private:
	Editor_UI::System& m_system;
	Entity* m_current_entity = nullptr;

	bool m_dirty = false;
};
