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
	Dev_Tools_Mode_Items(const Editor_UI::System&, const Item_Registry&, Inventory&, const Font&);
	void draw();
private:
	void rebuild(); // FIXME - maybe eliminate this by constructing dev tools after item registry is loaded?
	const Item_Registry& m_item_registry;
	Inventory& m_inventory;
	const Font& m_font;
	const Editor_UI::System& m_gui_system;

	Editor_UI::Context m_context;
	Editor_UI::Widgets::Pane* m_pane = nullptr;
};
