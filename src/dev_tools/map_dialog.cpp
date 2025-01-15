#include "map_dialog.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widgets/input.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "game/game_logic_state_normal.hpp"
#include "raylib/raylib.h"
#include "utils/function_wrapper.hpp"
#include "utils/log.hpp"
#include "utils/string.hpp"

static const int PANE_WIDTH = 400;
static const int PANE_HEIGHT = 300;

Dev_Tools_Map_Dialog::Dev_Tools_Map_Dialog(const Editor_UI::System& gui, Game_Logic_State_Normal& logic, Game_Facade& facade, const String& project_root) :
	m_gui{gui},
	m_logic{logic},
	m_facade{facade},
	m_project_root{project_root}
{
	m_pane = &m_context.add_pane({{}, {PANE_WIDTH, PANE_HEIGHT}});
	m_pane->colour = Editor_UI::Theme::SURFACE_CONTAINER_HIGHEST;

	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();
	m_pane->column.add_child(factory.make_icon_button(m_gui.ICON_CLOSE, [](){ SG_DEBUG("FIXME - close"); }));
	auto input = factory.make_input("Current map", Editor_UI::Theme::SURFACE_CONTAINER_HIGHEST);
	m_input = input.get();
	m_pane->column.add_child(move(input));
	m_pane->column.add_child(
		factory.make_button(
			"Change map",
			nullptr,
			[this](){
				m_facade.set_current_map(m_input->get_content());
			}
		)
	);
}

void Dev_Tools_Map_Dialog::draw(float dt)
{
	(void)m_facade;

	// Set pane transform
	m_pane->transform.position.x = GetScreenWidth() / 2 - PANE_WIDTH / 2;
	m_pane->transform.position.y = GetScreenHeight() / 2 - PANE_HEIGHT / 2;

	m_context.draw(dt);
}

void Dev_Tools_Map_Dialog::input_char(char character)
{
	m_context.input_char(character);
}

void Dev_Tools_Map_Dialog::input_key(int key)
{
	m_context.input_key(key);
}

void Dev_Tools_Map_Dialog::reset_map_input()
{
	m_input->set_content(get_relative_path(m_logic.get_map_filename(), m_project_root));
}
