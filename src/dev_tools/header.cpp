#include "header.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widgets/view_model_holder.hpp"
#include "game/game_logic.hpp"
#include "raylib/raylib.h"
#include "utils/move.hpp"
#include "utils/function_wrapper.hpp"

Dev_Tools_Header::Dev_Tools_Header(Game_Facade& facade, Game_Logic& game_logic, Game_Logic_State_Normal& logic_normal, const Editor_UI::System& gui, const String& project_root) :
	m_game_facade{facade},
	m_game_logic{game_logic},
	m_gui_system{gui},
	m_map_dialog{gui, logic_normal, project_root}
{
	// Build GUI
	Editor_UI::Widget_Factory factory = m_gui_system.get_widget_factory();
	m_pane = &m_context.add_pane(Recti{{0, 0}, {10000, Editor_UI::Theme::HEADER_HEIGHT}});
	//pane.colour = Editor_UI::Theme::SURFACE_CONTAINER;

	auto map_button = factory.make_icon_button(
		m_gui_system.ICON_MAP,
		[this](){
			m_map_dialog.toggle();
		}
	);

	auto save_button = factory.make_icon_button(
		m_gui_system.ICON_SAVE,
		[this](){
			m_game_facade.save_game();
		}
	);

	auto load_button = factory.make_icon_button(
		m_gui_system.ICON_RELOAD,
		[this](){
			m_game_logic.continue_game(); // FIXME - is 'continue_game' a good name for the function?
		}
	);

	auto row = factory.make_row();
	row->add_child(move(map_button));
	row->add_child(move(save_button));
	row->add_child(move(load_button));

	m_pane->column.add_child(move(row));
	m_pane->column.add_child(factory.make_view_model_holder(m_map_dialog));
}

void Dev_Tools_Header::draw(const String& map_filename, float dt)
{
	// Adjust pane size
	m_pane->transform.size.x = GetScreenWidth();

	(void)m_game_logic;
	(void)m_game_facade;
	(void)map_filename;

	m_context.draw(dt);
}

void Dev_Tools_Header::input_char(char character)
{
	m_context.input_char(character);
}

void Dev_Tools_Header::input_key(int key)
{
	m_context.input_key(key);
}
