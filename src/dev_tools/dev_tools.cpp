#include "dev_tools.hpp"
#include "dev_tools/mode_sequence.hpp"
#include "utils/log.hpp"
#include "map/map.hpp"
#include "io/user_directory_provider.hpp"
#include "utils/own_ptr.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widgets/nav_rail.hpp"
#include "graphics/editor_ui/widgets/view_model_holder.hpp"
#include "graphics/editor_ui/widgets/stack.hpp"
#include "graphics/editor_ui/widgets/absolute_pane.hpp"
#include "graphics/editor_ui/widgets/row.hpp"
#include "graphics/editor_ui/widgets/column.hpp"

Dev_Tools::Dev_Tools(Game_Facade& facade, Game_Logic& logic, Game_Logic_State_Normal& logic_normal, Sequence_Manager& seq_mgr, const Item_Registry& item_reg, Inventory& inv, const String& project_root) :
	m_header(facade, logic, logic_normal, m_gui, project_root),
	m_sequence(m_gui, seq_mgr, project_root),
	m_entity{m_gui},
	m_items(m_gui, item_reg, inv)
{
	Editor_UI::Theme theme; // Default theme

	// Set up GUI
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();

	// Header
	auto header_pane = factory.make_pane(Recti{{0, 0}, {10000, theme.HEADER_HEIGHT}}, true);
	header_pane->column.add_child(factory.make_view_model_holder(m_header));

	// Compose everything
	auto main_row = factory.make_row(true);
	main_row->add_child(make_nav_rail_pane());
	main_row->add_child(make_right_pane());

	auto main_column = factory.make_column();
	main_column->add_child(move(header_pane));
	main_column->add_child(move(main_row));

	m_context.set_top_widget(move(main_column));
}

Own_Ptr<Editor_UI::Widget> Dev_Tools::make_right_pane()
{
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();
	Editor_UI::Theme theme; // Default theme

	auto right_pane = factory.make_pane({{800, theme.HEADER_HEIGHT}, {400, 700}}, true);

	auto stack = factory.make_stack();
	m_right_pane_stack = stack.get();
	stack->add_child(factory.make_view_model_holder(m_items));
	stack->add_child(factory.make_view_model_holder(m_sequence));
	stack->add_child(factory.make_view_model_holder(m_entity));

	right_pane->column.add_child(move(stack));

	return right_pane;
}

Own_Ptr<Editor_UI::Widget> Dev_Tools::make_nav_rail_pane()
{
	Editor_UI::Theme theme; // Default theme
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();

	auto nav_pane = factory.make_pane({{0, theme.HEADER_HEIGHT}, {theme.NAV_WIDTH, 10000}}, false);
	auto nav_rail = factory.make_nav_rail();
	nav_rail->add_item(
		factory.make_nav_rail_item(
			m_gui.ICON_SEQUENCE,
			"Sequences",
			[this, rail = nav_rail.get()](){
				rail->set_active_index(0);
				m_right_pane_stack->set_current_widget(1);
				m_mode = Dev_Tools_Mode::sequence;
			}
		)
	);
	nav_rail->add_item(
		factory.make_nav_rail_item(
			m_gui.ICON_ENTITY,
			"Entities",
			[this, rail = nav_rail.get()](){
				rail->set_active_index(1);
				m_right_pane_stack->set_current_widget(2);
				m_mode = Dev_Tools_Mode::entities;
			}
		)
	);
	nav_rail->add_item(
		factory.make_nav_rail_item(
			m_gui.ICON_ITEMS,
			"Items",
			[this, rail = nav_rail.get()](){
				rail->set_active_index(2);
				m_right_pane_stack->set_current_widget(0);
				m_mode = Dev_Tools_Mode::items;
			}
		)
	);

	nav_pane->column.add_child(move(nav_rail));
	return nav_pane;
}

void Dev_Tools::draw(float dt)
{
	m_context.draw(dt);
}

void Dev_Tools::update(Map& map)
{
	m_sequence.rebuild();
	m_entity.rebuild(map.entities);
}

void Dev_Tools::input_char(char character)
{
	m_context.input_char(character);
}

void Dev_Tools::input_key(int key)
{
	m_context.input_key(key);
}
