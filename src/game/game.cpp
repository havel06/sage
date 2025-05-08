#include "game.hpp"
#include "game/game_logic.hpp"
#include "game_facade.hpp"
#include "input/input_event_provider.hpp"
#include "input/user_input.hpp"
#include "io/gui_loader.hpp"
#include "io/item_registry_loader.hpp"
#include "io/project_loader.hpp"
#include "sequence/event.hpp"
#include "utils/direction.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "utils/profiler.hpp"
#include <raylib/raylib.h>

Game::Game(const Project_Description& description, bool display_fps, bool no_auto_save, const Optional<String>& record_filename, Input_Event_Provider& input, bool headless) :
	m_input{input},
	m_user_dir_provider(description.name.data()),
	m_resource_system(description.path, m_game_facade),
	m_logic{m_saveloader, m_resource_system.sequence_manager, m_resource_system.map_manager, description.start_sequence, m_resource_system.character_profile_manager.get(description.default_character.data(), false)},
	m_game_facade(m_music_player, m_logic.state_normal, m_camera_controller, m_saveloader, m_logic, m_scriptable_gui, m_logic.party, no_auto_save),
	m_saveloader(m_user_dir_provider, m_resource_system, m_logic, m_camera_controller, m_scriptable_gui, description.path),
	m_camera_controller(m_camera),
	m_text_box_renderer(m_logic.state_normal.text_box),
	m_inventory_renderer(m_logic.state_normal.item_registry, m_logic.state_normal.inventory, m_resource_system.font_manager.get_default_font()),
	m_combat_controller(m_logic.state_combat.get_combat(), m_inventory_renderer),
	m_combat_renderer(m_logic.state_combat.get_combat(), m_combat_controller),
	m_quest_log_renderer(m_logic.state_normal.quest_log),
	m_main_menu(m_logic, m_resource_system.font_manager.get_default_font()),
	m_scriptable_gui{m_resource_system.gui_loader},
	m_debug_entity_renderer{m_camera},
	m_dev_tools(m_game_facade, m_logic, m_resource_system.sequence_manager, description.path),
	m_editor{m_resource_system.gui_loader},
	m_display_fps{display_fps}
{
	{
		SG_PROFILE_SCOPE("Item registry loading");
		// Item registry
		Item_Registry_Loader item_registry_loader(m_resource_system.texture_manager, m_resource_system.sequence_manager);
		item_registry_loader.load(m_logic.state_normal.item_registry, description.path);
	}

	{
		SG_PROFILE_SCOPE("GUI loading");
		// UI
		m_text_box_renderer.load(m_resource_system.gui_loader, description.gui_description.textbox_path);
		m_quest_log_renderer.load(m_resource_system.gui_loader, description.gui_description.quest_log_path, description.gui_description.quest_path);
		m_inventory_renderer.load(m_resource_system.gui_loader, description.gui_description.inventory_path, description.gui_description.inventory_slot_path);
		m_combat_controller.load(m_resource_system.gui_loader, description.gui_description.combat_menu_path, description.gui_description.combat_option_path);
		m_main_menu.load(m_resource_system.gui_loader, description.gui_description.main_menu_path, description.gui_description.main_menu_option_path);
	}

	m_record_filename = record_filename;
	m_initial_window_size = description.initial_window_size;
	m_headless = headless;
}

Game::~Game()
{
	m_game_facade.save_game();

	if (m_record_filename.has_value())
		m_replay_recorder.get_replay().save_to_file(m_record_filename.value().data());
}

bool Game::should_exit() const
{
	return m_logic.get_state() == Game_Logic_State::exit;
}

void Game::draw_frame(float time_delta)
{
	// Window size reset
	if (IsKeyPressed(KEY_F1))
		SetWindowSize(m_initial_window_size.x, m_initial_window_size.y);

	// Console toggle
	if (IsKeyPressed(KEY_F2))
		m_show_console = !m_show_console;

	// Dev mode switch
	if (IsKeyPressed(KEY_F3)) {
		if (m_mode == Mode::dev_tools) {
			SG_INFO("Switched to \"game\" mode.");
			m_mode = Mode::game;
		} else {
			SG_INFO("Switched to \"dev tools\" mode.");
			m_mode = Mode::dev_tools;
			m_dev_tools.rebuild();
		}
	}

	// Editor mode switch
	if (IsKeyPressed(KEY_F4)) {
		if (m_mode == Mode::editor) {
			SG_INFO("Switched to \"game\" mode.");
			m_mode = Mode::game;
		} else {
			SG_INFO("Switched to \"editor\" mode.");
			m_mode = Mode::editor;
			m_editor.rebuild();
		}
	}

	// Dev mode
	if (m_mode == Mode::dev_tools) {
		m_camera_controller.update(m_logic.state_normal.get_map(), m_logic.state_normal.get_player(), time_delta);
		if (!m_headless) {
			while (int character = GetCharPressed()) {
				if (character > 127) {
					SG_ERROR("Tried to input non-ascii character.");
				} else {
					m_dev_tools.input_char(character);
				}
			}
			while (int key = GetKeyPressed()) {
				m_dev_tools.input_key(key);
			}
			m_map_renderer.draw(m_logic.state_normal.get_map(), m_camera, time_delta);
			m_debug_entity_renderer.draw(m_logic.state_normal.get_map().entities);
			m_dev_tools.draw(time_delta);
		}
		return;
	}

	// Editor mode
	if (m_mode == Mode::editor && !m_headless) {
		while (int character = GetCharPressed()) {
			if (character > 127) {
				SG_ERROR("Tried to input non-ascii character.");
			} else {
				m_editor.input_char(character);
			}
		}
		while (int key = GetKeyPressed()) {
			m_editor.input_key(key);
		}
		m_editor.draw(time_delta);
		return;
	}

	// Mode::game related

	// Input
	{
		if (m_record_filename.has_value())
			m_replay_recorder.begin_frame(time_delta);

		m_input.process(*this);
	}

	// Close inventory if empty
	if (m_show_inventory && m_logic.state_normal.inventory.is_empty())
		m_show_inventory = false;
	
	m_resource_system.unload_free_resources();
	m_music_player.update(); // FIXME - should this be in Game_Logic?

	// Main logic update
	m_logic.update(time_delta);

	// Normal mode update
	if (m_logic.get_state() == Game_Logic_State::normal) {
		if (!m_show_inventory && !m_show_quest_log)
			do_player_movement();

		m_camera_controller.update(m_logic.state_normal.get_map(), m_logic.state_normal.get_player(), time_delta);
	}

	// Render
	if (!m_headless)
		render(time_delta);
}

void Game::render(float time_delta)
{
	// Main menu rendering
	if (m_logic.get_state() == Game_Logic_State::main_menu_to_normal ||
		m_logic.get_state() == Game_Logic_State::main_menu_to_combat)
	{
		m_main_menu.draw(time_delta);
	}

	// Normal rendering
	if (m_logic.get_state() == Game_Logic_State::normal) {
		m_map_renderer.draw(m_logic.state_normal.get_map(), m_camera, time_delta);
		m_scriptable_gui.draw(time_delta);
		m_text_box_renderer.draw(time_delta);

		m_quest_log_renderer.show(m_show_quest_log);
		m_quest_log_renderer.draw(time_delta);

		m_inventory_renderer.show(m_show_inventory);
		m_inventory_renderer.draw(time_delta);
	}

	// Combat rendering
	if (m_logic.get_state() == Game_Logic_State::combat) {
		m_combat_renderer.draw(time_delta);
		m_combat_controller.draw(time_delta);
		m_inventory_renderer.draw(time_delta);
		m_scriptable_gui.draw(time_delta);
	}

	// Console
	if (m_show_console) {
		m_console.draw(time_delta);
	}

	// FPS
	if (m_display_fps) {
		DrawRectangle(0, 0, 120, 40, Color{0, 0, 0, 200});
		DrawFPS(10, 10);
	}

}

void Game::do_player_movement()
{
	if (m_go_up) {
		m_logic.state_normal.move_player(Direction::up);
	} else if (m_go_down) {
		m_logic.state_normal.move_player(Direction::down);
	} else if (m_go_right) {
		m_logic.state_normal.move_player(Direction::right);
	} else if (m_go_left) {
		m_logic.state_normal.move_player(Direction::left);
	}
}

void Game::handle_input_event(Input_Event event)
{
	if (m_record_filename.has_value())
		m_replay_recorder.capture_event(event);

	// Direction input
	switch (event) {
		case Input_Event::up_pressed:
			m_go_up = true;
			break;
		case Input_Event::up_released:
			m_go_up = false;
			break;
		case Input_Event::down_pressed:
			m_go_down = true;
			break;
		case Input_Event::down_released:
			m_go_down = false;
			break;
		case Input_Event::left_pressed:
			m_go_left = true;
			break;
		case Input_Event::left_released:
			m_go_left = false;
			break;
		case Input_Event::right_pressed:
			m_go_right = true;
			break;
		case Input_Event::right_released:
			m_go_right = false;
			break;
		default:
			break;
	}

	switch (m_logic.get_state()) {
		case Game_Logic_State::normal:
			if (m_show_inventory)
				handle_input_inventory(event);
			else if (m_show_quest_log)
				handle_input_quest_log(event);
			else
				handle_input_normal(event);
			break;
		case Game_Logic_State::combat:
			handle_input_combat(event);
			break;
		case Game_Logic_State::main_menu_to_normal:
		case Game_Logic_State::main_menu_to_combat:
			handle_input_main_menu(event);
			break;
		case Game_Logic_State::exit:
			break;
	}
}

void Game::handle_input_normal(Input_Event event)
{
	switch (event) {
		case Input_Event::accept:
			if (m_logic.state_normal.text_box.contains_message())
				m_logic.state_normal.text_box.advance();
			else
				m_logic.state_normal.player_interact();
			break;

		case Input_Event::open_inventory:
			if (!m_logic.state_normal.inventory.is_empty())
				m_show_inventory = true;
			break;

		case Input_Event::open_quest_log:
			m_show_quest_log = true;
			break;

		default:
			break;
	}
}

void Game::handle_input_inventory(Input_Event event)
{
	switch (event) {
		case Input_Event::up_pressed:
			m_inventory_renderer.input_direction(Direction::up);
			break;

		case Input_Event::down_pressed:
			m_inventory_renderer.input_direction(Direction::down);
			break;

		case Input_Event::left_pressed:
			m_inventory_renderer.input_direction(Direction::left);
			break;

		case Input_Event::right_pressed:
			m_inventory_renderer.input_direction(Direction::right);
			break;

		case Input_Event::open_inventory:
		case Input_Event::escape:
			m_show_inventory = false;
			break;

		case Input_Event::accept:
			m_inventory_renderer.input_click();
			break;

		default:
			break;
	}
}

void Game::handle_input_quest_log(Input_Event event)
{
	if (event == Input_Event::escape || event == Input_Event::open_quest_log) {
		m_show_quest_log = false;
	}
}

void Game::handle_input_main_menu(Input_Event event)
{
	switch (event) {
		case Input_Event::up_pressed:
			m_main_menu.input_direction(Direction::up);
			break;

		case Input_Event::down_pressed:
			m_main_menu.input_direction(Direction::down);
			break;

		case Input_Event::left_pressed:
			m_main_menu.input_direction(Direction::left);
			break;

		case Input_Event::right_pressed:
			m_main_menu.input_direction(Direction::right);
			break;

		case Input_Event::accept:
			m_main_menu.enter();
			break;

		default:
			break;
	}
}

void Game::handle_input_combat(Input_Event event)
{
	switch (event) {
		case Input_Event::up_pressed:
			m_combat_controller.input_direction(Direction::up);
			break;

		case Input_Event::down_pressed:
			m_combat_controller.input_direction(Direction::down);
			break;

		case Input_Event::left_pressed:
			m_combat_controller.input_direction(Direction::left);
			break;

		case Input_Event::right_pressed:
			m_combat_controller.input_direction(Direction::right);
			break;

		case Input_Event::accept:
			m_combat_controller.input_enter();
			break;

		case Input_Event::escape:
			m_combat_controller.input_escape();
			break;

		default:
			break;
	}
}
