#include "header.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/widgets/input.hpp"
#include "raylib/raylib.h"
#include "utils/move.hpp"

Dev_Tools_Header::Dev_Tools_Header(Game_Facade& facade, Game_Logic& game_logic, const Editor_UI::System& gui, const String& project_root) :
	m_game_facade{facade},
	m_game_logic{game_logic},
	m_gui_system{gui},
	m_project_root{project_root}
{
	// Build GUI
	Editor_UI::Widget_Factory factory = m_gui_system.get_widget_factory();
	m_pane = &m_context.add_pane(Recti{{0, 0}, {10000, Editor_UI::Theme::HEADER_HEIGHT}});
	//pane.colour = Editor_UI::Theme::SURFACE_CONTAINER;

	auto map_input = factory.make_input("Current map");
	m_map_input = map_input.get();

	m_pane->column.add_child(move(map_input));
}

void Dev_Tools_Header::draw(const String& map_filename)
{
	// Adjust pane size
	m_pane->transform.size.x = GetScreenWidth();

	(void)m_game_logic;
	(void)m_game_facade;

	m_map_input->content = map_filename;
	m_context.draw();
}
