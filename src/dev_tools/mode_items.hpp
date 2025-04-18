#pragma once

#include "utils/string.hpp"
#include "graphics/editor_ui/context.hpp"
#include "graphics/editor_ui/state.hpp"

// fwd
class Item_Registry;
class Inventory;
struct Font;
namespace Editor_UI {
	class System;
}

class Dev_Tools_Mode_Items : public Editor_UI::State
{
public:
	Dev_Tools_Mode_Items(const Item_Registry&, Inventory&);

	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme& theme) override;
	bool is_dirty() const override;
private:
	const Item_Registry& m_item_registry;
	Inventory& m_inventory;
};
