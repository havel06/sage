#pragma once

#include "utils/string.hpp"
#include "graphics/editor_ui/context.hpp"

// fwd
class Item_Registry;
class Inventory;
struct Font;
namespace Editor_UI {
	class System;
}
namespace Editor_UI::Widgets {
	class Pane;
	class Column;
}

class Dev_Tools_Mode_Items
{
public:
	Dev_Tools_Mode_Items(const Editor_UI::System&, const Item_Registry&, Inventory&);
	void draw(float dt);
private:
	void rebuild();
	const Item_Registry& m_item_registry;
	Inventory& m_inventory;
	const Editor_UI::System& m_gui_system;

	Editor_UI::Context m_context;
	Editor_UI::Widgets::Pane* m_pane = nullptr;
};
