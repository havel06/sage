#pragma once

#include "utils/string.hpp"
#include "graphics/editor_ui/context.hpp"
#include "graphics/editor_ui/view_model.hpp"

// fwd
class Item_Registry;
class Inventory;
struct Font;
namespace Editor_UI {
	class System;
}
namespace Editor_UI::Widgets {
	class Absolute_Pane;
	class Column;
}

class Dev_Tools_Mode_Items : public Editor_UI::View_Model
{
public:
	Dev_Tools_Mode_Items(const Editor_UI::System&, const Item_Registry&, Inventory&);

	Own_Ptr<Editor_UI::Widget> build() override;
	bool is_dirty() const override;
private:
	const Item_Registry& m_item_registry;
	Inventory& m_inventory;
	const Editor_UI::System& m_gui_system;
};
