#include "game.hpp"
#include "game_facade.hpp"
#include "graphics/ui/widget.hpp"
#include "io/gui_loader.hpp"
#include "io/item_registry_loader.hpp"
#include "io/project_loader.hpp"
#include "sequence/event.hpp"
#include "utils/direction.hpp"
#include "utils/log.hpp"
#include <raylib/raylib.h>

Game::Game(const Project_Description& description) :
	m_game_facade(m_resource_system.sequence_manager, m_music_player, m_logic_normal, m_camera_controller, m_map_saveloader, m_game_saveloader, m_logic),
	m_sequence_loader(m_resource_system, m_game_facade),
	m_resource_system(description.path, m_sequence_loader, m_sequence_saveloader),
	m_combat(m_logic_normal.party),
	m_logic_normal(m_resource_system.sequence_manager,m_map_saveloader, m_resource_system.map_manager, description.start_sequence),
	m_logic_combat(m_logic, m_combat),
	m_logic{m_game_saveloader, m_logic_normal, m_logic_combat},
	m_combat_controller(m_combat),
	m_map_saveloader(m_resource_system.texture_manager, description.path),
	m_sequence_saveloader(description.path),
	m_game_saveloader(description.path, m_game_facade, m_camera, m_logic_normal.inventory, m_logic_normal.quest_log, m_resource_system.sequence_manager),
	m_camera_controller(m_camera),
	m_text_box_renderer(m_logic_normal.text_box),
	m_inventory_renderer(m_logic_normal.item_registry, m_logic_normal.inventory),
	m_combat_renderer(m_logic_normal.party, m_combat),
	m_quest_log_renderer(m_logic_normal.quest_log),
	m_main_menu(m_logic),
	m_dev_tools(m_game_facade, m_resource_system.sequence_manager, description.path)
{
	// FIXME - make the constructor smaller by injecting into member classes via their constructors

	// Item registry
	Item_Registry_Loader item_registry_loader(m_resource_system.texture_manager);
	item_registry_loader.load(m_logic_normal.item_registry, description.path);

	// FIXME - try to remove this block
	// UI
	GUI_Loader gui_loader(m_resource_system.font_manager, m_resource_system.texture_manager);
	m_text_box_renderer.load(gui_loader, description.path, description.gui_description.textbox_path);
	m_quest_log_renderer.load(gui_loader, description.path, description.gui_description.quest_log_path, description.gui_description.quest_path);
	m_inventory_renderer.load(gui_loader, description.path, description.gui_description.inventory_path, description.gui_description.inventory_slot_path);
	m_combat_controller.load(gui_loader, description.path, description.gui_description.combat_menu_path, description.gui_description.combat_option_path);
	m_main_menu.load(gui_loader, description.path, description.gui_description.main_menu_path, description.gui_description.main_menu_option_path);

	// Savegame location
	m_map_saveloader.set_save_directory("savegame");
	m_sequence_saveloader.set_save_directory("savegame");
	m_game_saveloader.set_save_directory("savegame");

	// Set up main character profile
	m_logic_normal.party.main_character() = m_resource_system.character_profile_manager.get(description.default_character.data(), false);
}

Game::~Game()
{
	m_game_facade.save_game();
}

bool Game::should_exit() const
{
	return m_logic.get_state() == Game_Logic_State::exit;
}

void Game::draw_frame(float time_delta)
{
	if (m_logic.get_state() == Game_Logic_State::main_menu) {
		process_main_menu_input();
		m_main_menu.draw(time_delta);
		return;
	}

	// FIXME - refactor this function
	if (IsKeyPressed(KEY_F3))
		m_dev_mode = !m_dev_mode;

	if (m_dev_mode) {
		m_camera_controller.update(m_logic_normal.get_map(), m_logic_normal.get_player());
		m_map_renderer.draw(m_logic_normal.get_map(), m_camera, time_delta);
		m_dev_tools.draw(m_logic_normal.get_map());
		return;
	}

	m_music_player.update();
	m_logic.update(time_delta);

	if (m_logic.get_state() == Game_Logic_State::normal) {
		// Normal mode
		process_normal_input();
		m_camera_controller.update(m_logic_normal.get_map(), m_logic_normal.get_player());
		m_map_renderer.draw(m_logic_normal.get_map(), m_camera, time_delta);
		m_text_box_renderer.draw();

		if (m_show_inventory) {
			m_inventory_renderer.draw();
		} else if (m_show_quest_log) {
			m_quest_log_renderer.draw();
		}
	} else {
		// Combat mode
		process_combat_input();
		m_combat_renderer.draw(time_delta);
		m_combat_controller.draw();
	}
}

void Game::process_normal_input()
{
	if (IsKeyPressed(KEY_ENTER)) {
		if (m_logic_normal.text_box.contains_message())
			m_logic_normal.text_box.advance();
		else
			m_logic_normal.player_interact();
	} else if (IsKeyPressed(KEY_I)) {
		m_show_inventory = !m_show_inventory;
	} else if (IsKeyPressed(KEY_Q)) {
		m_show_quest_log = !m_show_quest_log;
	}

	if (IsKeyDown(KEY_UP)) {
		m_logic_normal.move_player(Direction::up);
	} else if (IsKeyDown(KEY_DOWN)) {
		m_logic_normal.move_player(Direction::down);
	} else if (IsKeyDown(KEY_RIGHT)) {
		m_logic_normal.move_player(Direction::right);
	} else if (IsKeyDown(KEY_LEFT)) {
		m_logic_normal.move_player(Direction::left);
	}
}

void Game::process_main_menu_input()
{
	if (IsKeyPressed(KEY_UP)) {
		m_main_menu.input_direction(Direction::up);
	} else if (IsKeyPressed(KEY_DOWN)) {
		m_main_menu.input_direction(Direction::down);
	} else if (IsKeyPressed(KEY_RIGHT)) {
		m_main_menu.input_direction(Direction::right);
	} else if (IsKeyPressed(KEY_LEFT)) {
		m_main_menu.input_direction(Direction::left);
	} else if (IsKeyPressed(KEY_ENTER)) {
		m_main_menu.enter();
	}
}

void Game::process_combat_input()
{
	if (IsKeyPressed(KEY_UP)) {
		m_combat_controller.input_direction(Direction::up);
	} else if (IsKeyPressed(KEY_DOWN)) {
		m_combat_controller.input_direction(Direction::down);
	} else if (IsKeyPressed(KEY_RIGHT)) {
		m_combat_controller.input_direction(Direction::right);
	} else if (IsKeyPressed(KEY_LEFT)) {
		m_combat_controller.input_direction(Direction::left);
	} else if (IsKeyPressed(KEY_ENTER)) {
		m_combat_controller.enter();
	}
}
