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

Game::Game(const Project_Description& description, bool display_fps, bool no_auto_save) :
	m_game_facade(m_resource_system.sequence_manager, m_music_player, m_logic_normal, m_camera_controller, m_map_saveloader, m_game_saveloader, m_logic, m_scriptable_gui, m_combat, m_party, no_auto_save),
	m_sequence_loader(description.path, m_resource_system, m_game_facade, m_gui_loader),
	m_resource_system(description.path, m_sequence_loader, m_sequence_saveloader),
	m_savegame_dir_provider(description.name.data()),
	m_map_saveloader(m_resource_system.texture_manager, m_savegame_dir_provider, description.path),
	m_sequence_saveloader(m_savegame_dir_provider, description.path),
	m_game_saveloader(m_savegame_dir_provider, description.path, m_logic_normal, m_camera, m_logic_normal.inventory, m_logic_normal.quest_log, m_resource_system.sequence_manager, m_resource_system.character_profile_manager, m_party),
	m_party(m_resource_system.character_profile_manager.get(description.default_character.data(), false)),
	m_combat(m_party),
	m_logic_normal(m_party, m_resource_system.sequence_manager,m_map_saveloader, m_resource_system.map_manager),
	m_logic_combat(m_logic, m_combat, m_resource_system.sequence_manager),
	m_logic{m_game_saveloader, m_resource_system.sequence_manager, m_logic_normal, m_logic_combat, description.start_sequence},
	m_gui_loader(m_resource_system.font_manager, m_resource_system.texture_manager, description.path),
	m_camera_controller(m_camera),
	m_text_box_renderer(m_logic_normal.text_box),
	m_inventory_renderer(m_logic_normal.item_registry, m_logic_normal.inventory),
	m_combat_controller(m_combat, m_inventory_renderer),
	m_combat_renderer(m_party, m_combat),
	m_quest_log_renderer(m_logic_normal.quest_log),
	m_main_menu(m_logic, m_resource_system.font_manager.get_default_font()),
	m_dev_tools(m_game_facade, m_logic, m_resource_system.sequence_manager, m_logic_normal.item_registry, m_logic_normal.inventory, description.path),
	m_display_fps{display_fps}
{
	// Item registry
	Item_Registry_Loader item_registry_loader(m_resource_system.texture_manager, m_resource_system.sequence_manager);
	item_registry_loader.load(m_logic_normal.item_registry, description.path);

	// UI
	m_text_box_renderer.load(m_gui_loader, description.gui_description.textbox_path);
	m_quest_log_renderer.load(m_gui_loader, description.gui_description.quest_log_path, description.gui_description.quest_path);
	m_inventory_renderer.load(m_gui_loader, description.gui_description.inventory_path, description.gui_description.inventory_slot_path);
	m_combat_controller.load(m_gui_loader, description.gui_description.combat_menu_path, description.gui_description.combat_option_path);
	m_main_menu.load(m_gui_loader, description.gui_description.main_menu_path, description.gui_description.main_menu_option_path);
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
	// FIXME - refactor this function

	m_resource_system.unload_free_resources();
	m_music_player.update();

	if (m_logic.get_state() == Game_Logic_State::main_menu) {
		process_main_menu_input();
		m_main_menu.draw(time_delta);
		return;
	}

	if (IsKeyPressed(KEY_F3))
		m_dev_mode = !m_dev_mode;

	if (m_dev_mode) {
		m_camera_controller.update(m_logic_normal.get_map(), m_logic_normal.get_player(), time_delta);
		m_map_renderer.draw(m_logic_normal.get_map(), m_camera, time_delta);
		m_dev_tools.draw(m_logic_normal.get_map(), m_logic_normal.get_map_filename());
		return;
	}

	m_logic.update(time_delta);

	if (m_logic.get_state() == Game_Logic_State::normal) {
		// Normal mode
		if (m_show_inventory)
			process_inventory_input();
		else
			process_normal_input();

		m_camera_controller.update(m_logic_normal.get_map(), m_logic_normal.get_player(), time_delta);
		m_map_renderer.draw(m_logic_normal.get_map(), m_camera, time_delta);
		m_scriptable_gui.draw(time_delta);
		m_text_box_renderer.draw(time_delta);

		m_quest_log_renderer.show(m_show_quest_log);
		m_quest_log_renderer.draw(time_delta);

		m_inventory_renderer.show(m_show_inventory);
	} else {
		// Combat mode
		process_combat_input();
		m_combat_renderer.draw(time_delta);
		m_combat_controller.draw(time_delta);
	}

	m_inventory_renderer.draw(time_delta);

	if (m_display_fps)
		DrawFPS(10, 10);
}

void Game::process_normal_input()
{
	if (is_action_pressed_accept()) {
		if (m_logic_normal.text_box.contains_message())
			m_logic_normal.text_box.advance();
		else
			m_logic_normal.player_interact();
	} else if (is_action_pressed_inventory()) {
		m_show_inventory = true;
	} else if (is_action_pressed_questlog()) {
		m_show_quest_log = !m_show_quest_log;
	}

	if (is_action_down_up()) {
		m_logic_normal.move_player(Direction::up);
	} else if (is_action_down_down()) {
		m_logic_normal.move_player(Direction::down);
	} else if (is_action_down_right()) {
		m_logic_normal.move_player(Direction::right);
	} else if (is_action_down_left()) {
		m_logic_normal.move_player(Direction::left);
	}
}

void Game::process_inventory_input()
{
	if (is_action_pressed_up()) {
		m_inventory_renderer.input_direction(Direction::up);
	} else if (is_action_pressed_down()) {
		m_inventory_renderer.input_direction(Direction::down);
	} else if (is_action_pressed_right()) {
		m_inventory_renderer.input_direction(Direction::right);
	} else if (is_action_pressed_left()) {
		m_inventory_renderer.input_direction(Direction::left);
	} else if (is_action_pressed_inventory()) {
		m_show_inventory = false;
	} else if (is_action_pressed_accept()) {
		m_inventory_renderer.input_click();
	}
}

void Game::process_main_menu_input()
{
	if (is_action_pressed_up()) {
		m_main_menu.input_direction(Direction::up);
	} else if (is_action_pressed_down()) {
		m_main_menu.input_direction(Direction::down);
	} else if (is_action_pressed_right()) {
		m_main_menu.input_direction(Direction::right);
	} else if (is_action_pressed_left()) {
		m_main_menu.input_direction(Direction::left);
	} else if (is_action_pressed_accept()) {
		m_main_menu.enter();
	}
}

void Game::process_combat_input()
{
	if (is_action_pressed_up()) {
		m_combat_controller.input_direction(Direction::up);
	} else if (is_action_pressed_down()) {
		m_combat_controller.input_direction(Direction::down);
	} else if (is_action_pressed_right()) {
		m_combat_controller.input_direction(Direction::right);
	} else if (is_action_pressed_left()) {
		m_combat_controller.input_direction(Direction::left);
	} else if (is_action_pressed_accept()) {
		m_combat_controller.input_enter();
	}
}

bool Game::is_action_pressed_up()
{
	return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP) || IsKeyPressed(KEY_UP);
}

bool Game::is_action_pressed_down()
{
	return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN) || IsKeyPressed(KEY_DOWN);
}

bool Game::is_action_pressed_left()
{
	return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) || IsKeyPressed(KEY_LEFT);
}

bool Game::is_action_pressed_right()
{
	return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) || IsKeyPressed(KEY_RIGHT);
}

bool Game::is_action_down_up()
{
	return IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP) || IsKeyDown(KEY_UP);
}

bool Game::is_action_down_down()
{
	return IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN) || IsKeyDown(KEY_DOWN);
}

bool Game::is_action_down_left()
{
	return IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) || IsKeyDown(KEY_LEFT);
}

bool Game::is_action_down_right()
{
	return IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) || IsKeyDown(KEY_RIGHT);
}

bool Game::is_action_pressed_accept()
{
	return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) || IsKeyPressed(KEY_ENTER);
}

bool Game::is_action_pressed_inventory()
{
	return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT) || IsKeyPressed(KEY_I);
}

bool Game::is_action_pressed_questlog()
{
	return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP) || IsKeyPressed(KEY_Q);
}
