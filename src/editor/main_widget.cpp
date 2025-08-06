#include "main_widget.hpp"

#include "editor/main_nav.hpp"
#include "editor/mode_general.hpp"
#include "editor/mode_gui.hpp"
#include "editor/mode_items.hpp"
#include "graphics/editor_ui/factories/row.hpp"
#include "graphics/editor_ui/factories/stateful.hpp"

namespace Editor
{

Main_Widget::Main_Widget(GUI_Loader& gui_loader, Item_Registry& item_registry) :
	m_gui_loader{gui_loader},
	m_item_registry{item_registry}
{
}

Own_Ptr<Editor_UI::Widget_Factory> Main_Widget::build(const Editor_UI::Theme&)
{
	using namespace Editor_UI::Factories;

	(void)m_gui_loader;

	return Row::make(false)
		->add(Stateful::make(make_own_ptr<Main_Nav>()))
		//->add(Stateful::make(make_own_ptr<Mode_GUI>(m_gui_loader)));
		//->add(Stateful::make(make_own_ptr<Mode_General>()));
		->add(Stateful::make(make_own_ptr<Mode_Items>(m_item_registry)));
}

}
