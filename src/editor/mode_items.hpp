#pragma once

#include "graphics/editor_ui/state.hpp"
#include "graphics/editor_ui/widgets/input_state.hpp"

class GUI_Loader;
class Item_Registry;

namespace Editor
{

class Mode_Items : public Editor_UI::State
{
public:
	Mode_Items(Item_Registry& item_registry);
	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme&) override;
	bool is_dirty() const override { return m_dirty; }
private:
	Item_Registry& m_item_registry;

	bool m_dirty = true;
};

}
