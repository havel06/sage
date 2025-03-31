#include "dev_tools.hpp"
#include "dev_tools/header.hpp"
#include "dev_tools/mode_sequence.hpp"
#include "graphics/editor_ui/widget.hpp"
#include "utils/log.hpp"
#include "map/map.hpp"
#include "io/user_directory_provider.hpp"
#include "utils/own_ptr.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widgets/nav_rail.hpp"
#include "graphics/editor_ui/widgets/view_model_holder.hpp"
#include "graphics/editor_ui/widgets/stack.hpp"
#include "graphics/editor_ui/widgets/absolute_pane.hpp"
#include "graphics/editor_ui/widgets/relative_pane.hpp"
#include "graphics/editor_ui/widgets/block.hpp"
#include "graphics/editor_ui/widgets/row.hpp"
#include "graphics/editor_ui/widgets/column.hpp"
#include "graphics/editor_ui/widgets/stateful.hpp"
#include "game/game_logic.hpp"

Dev_Tools::Dev_Tools(Game_Facade& facade, Game_Logic& logic, Sequence_Manager& seq_mgr, const String& project_root)
{
	// Set up GUI
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();

	auto header = make_own_ptr<Editor_UI::Widgets::Stateful>(
		make_own_ptr<Dev_Tools_Header>(m_gui.get_font(), facade, logic, m_gui, project_root)
	);

	auto mode_items = make_own_ptr<Editor_UI::Widgets::Stateful>(
		make_own_ptr<Dev_Tools_Mode_Items>(m_gui, logic.state_normal.item_registry, logic.state_normal.inventory)
	);

	auto mode_seq = make_own_ptr<Editor_UI::Widgets::Stateful>(
		make_own_ptr<Dev_Tools_Mode_Sequence>(m_gui, seq_mgr, project_root)
	);

	auto mode_entity = make_own_ptr<Editor_UI::Widgets::Stateful>(
		make_own_ptr<Dev_Tools_Mode_Entity>(m_gui, logic.state_normal.get_map().entities)
	);

	// Compose everything
	auto main_row = factory.make_row(true);
	main_row->add_child(make_nav_rail_pane());
	main_row->add_child(make_right_pane(move(mode_items), move(mode_seq), move(mode_entity)));

	auto main_column = factory.make_column(Editor_UI::Widgets::Column_Padding::none);
	main_column->add_child(make_header_pane(move(header)));
	main_column->add_child(move(main_row));

	m_context.set_top_widget(move(main_column));
}

void Dev_Tools::rebuild()
{
	// TODO
}

Own_Ptr<Editor_UI::Widget> Dev_Tools::make_header_pane(Own_Ptr<Editor_UI::Widget>&& header)
{
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();
	Editor_UI::Theme theme; // Default theme

	auto header_pane = factory.make_relative_pane(true);
	header_pane->column.add_child(move(header));
	return factory.make_block(move(header_pane), {20000, theme.HEADER_HEIGHT});
}

Own_Ptr<Editor_UI::Widget> Dev_Tools::make_right_pane(Own_Ptr<Editor_UI::Widget>&& mode_items, Own_Ptr<Editor_UI::Widget>&& mode_seq, Own_Ptr<Editor_UI::Widget>&& mode_entity)
{
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();

	auto right_pane = factory.make_relative_pane(true);

	auto stack = factory.make_stack();
	m_right_pane_stack = stack.get();
	stack->add_child(move(mode_items));
	stack->add_child(move(mode_seq));
	stack->add_child(move(mode_entity));

	right_pane->column.add_child(move(stack));

	return factory.make_block(move(right_pane), {500, 20000});
}

Own_Ptr<Editor_UI::Widget> Dev_Tools::make_nav_rail_pane()
{
	Editor_UI::Theme theme; // Default theme
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();

	auto nav_pane = factory.make_relative_pane(false);
	auto nav_rail = factory.make_nav_rail(
		[this](int index){
			switch (index) {
				case 0:
					m_right_pane_stack->set_current_widget(1);
					m_mode = Dev_Tools_Mode::sequence;
					break;
				case 1:
					m_right_pane_stack->set_current_widget(2);
					m_mode = Dev_Tools_Mode::entities;
					break;
				case 2:
					m_right_pane_stack->set_current_widget(0);
					m_mode = Dev_Tools_Mode::items;
					break;
			}
		}
	);
	nav_rail->add_item(
		factory.make_nav_rail_item(
			m_gui.ICON_SEQUENCE,
			"Sequences"
		)
	);
	nav_rail->add_item(
		factory.make_nav_rail_item(
			m_gui.ICON_ENTITY,
			"Entities"
		)
	);
	nav_rail->add_item(
		factory.make_nav_rail_item(
			m_gui.ICON_ITEMS,
			"Items"
		)
	);

	nav_pane->column.add_child(move(nav_rail));
	return factory.make_block(move(nav_pane), {theme.NAV_WIDTH, 20000});
}

void Dev_Tools::draw(float dt)
{
	m_context.draw(dt);
}

void Dev_Tools::input_char(char character)
{
	m_context.input_char(character);
}

void Dev_Tools::input_key(int key)
{
	m_context.input_key(key);
}
