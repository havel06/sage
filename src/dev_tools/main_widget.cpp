#include "main_widget.hpp"
#include "dev_tools/header.hpp"
#include "dev_tools/mode_entity.hpp"
#include "dev_tools/mode_items.hpp"
#include "dev_tools/mode_sequence.hpp"
#include "game/game_logic.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/constrained_container.hpp"
#include "graphics/editor_ui/factories/nav_rail.hpp"
#include "graphics/editor_ui/factories/relative_pane.hpp"
#include "graphics/editor_ui/factories/row.hpp"
#include "graphics/editor_ui/factories/stateful.hpp"
#include "graphics/editor_ui/state.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"

Dev_Tools_Main_Widget::Dev_Tools_Main_Widget(
		Game_Facade& facade,
		Game_Logic& logic,
		Sequence_Manager& sequence_manager,
		String project_root) :
	m_game_facade{facade},
	m_game_logic{logic},
	m_sequence_manager{sequence_manager},
	m_project_root{project_root}
{
}


Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Main_Widget::build(const Editor_UI::Theme& theme)
{
	m_dirty = false;
	using namespace Editor_UI::Factories;

	return Column::make(Column::Padding::none)
		->add(make_header_pane())
		->add(Row::make(true)
			->add(make_nav_rail_pane(theme))
			->add(make_right_pane())
		);
}

bool Dev_Tools_Main_Widget::is_dirty() const
{
	return m_dirty;
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Main_Widget::make_right_pane()
{
	auto make_mode_widget = [this]() -> Own_Ptr<Editor_UI::State> {
		switch (m_mode) {
			case Mode::entities:
				return make_own_ptr<Dev_Tools_Mode_Entity>(m_game_logic.state_normal.get_map().entities);
			case Mode::sequence:
				return make_own_ptr<Dev_Tools_Mode_Sequence>(m_sequence_manager, m_project_root);
			case Mode::items:
				return make_own_ptr<Dev_Tools_Mode_Items>(m_game_logic.state_normal.item_registry, m_game_logic.state_normal.inventory);
		}
	};

	using namespace Editor_UI::Factories;

	return Constrained_Container::make({500, 20000},
		Relative_Pane::make(true,
			Stateful::make(make_mode_widget())
		)
	);
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Main_Widget::make_nav_rail_pane(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	auto callback = [this](int index){
		m_mode = (Mode)index;
		m_dirty = true;
	};

	// FIXME - get width from theme?
	return Constrained_Container::make(Vec2i{80, 20000},
		Relative_Pane::make(false,
			Nav_Rail::make(callback, (int)m_mode)
				->add(theme.font, "Entities", theme.ICON_ENTITY)
				->add(theme.font, "Sequences", theme.ICON_SEQUENCE)
				->add(theme.font, "Items", theme.ICON_ITEMS)
		)
	);
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Main_Widget::make_header_pane()
{
	using namespace Editor_UI::Factories;

	// FIXME - get height from theme?
	return Constrained_Container::make(Vec2i{20000, 64},
		Relative_Pane::make(true,
			Stateful::make(make_own_ptr<Dev_Tools_Header>(m_game_facade, m_game_logic, m_project_root))
		)
	);
}
