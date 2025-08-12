#pragma once

#include "graphics/editor_ui/state.hpp"
#include "graphics/editor_ui/widgets/input_state.hpp"


struct Item;

namespace Editor
{

class Item_Edit_Dialog : public Editor_UI::State
{
public:
	Item_Edit_Dialog(Item& item);
	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme&) override;
	bool is_dirty() const override { return m_dirty; }
private:
	//Item& m_item;

	Editor_UI::Widgets::Input_State m_input_state_id;
	Editor_UI::Widgets::Input_State m_input_state_name;
	Editor_UI::Widgets::Input_State m_input_state_sequence;

	bool m_dirty = true;
};

}
