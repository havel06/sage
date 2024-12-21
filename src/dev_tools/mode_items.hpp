#pragma once

#include "utils/string.hpp"
#include "graphics/editor_ui/context.hpp"
#include "graphics/editor_ui/widgets/column.hpp"

class Item_Registry;
class Inventory;
struct Font;

class Dev_Tools_Mode_Items
{
public:
	Dev_Tools_Mode_Items(const Item_Registry&, Inventory&, const Font&);
	Editor_UI::Context& get_context() { return m_context; }
	void rebuild(); // FIXME - eliminate this by constructing dev tools after item registry is loaded?
private:
	const Item_Registry& m_item_registry;
	Inventory& m_inventory;
	const Font& m_font;

	Editor_UI::Context m_context;
	Editor_UI::Widgets::Column* m_column = nullptr;
};
