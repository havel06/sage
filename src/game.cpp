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

Game::Game(const char* project_path) :
	m_game_facade(m_resource_system.map_manager, m_resource_system.sequence_manager, m_music_player, m_logic, m_camera_controller, m_map_saveloader, m_game_saveloader),
	m_sequence_loader(m_resource_system, m_game_facade),
	m_resource_system(project_path, m_sequence_loader, m_sequence_saveloader),
	m_combat_controller(m_logic.combat),
	m_map_saveloader(m_resource_system.texture_manager, project_path),
	m_sequence_saveloader(project_path),
	m_game_saveloader(project_path, m_game_facade, m_camera, m_logic.inventory, m_logic.quest_log, m_resource_system.sequence_manager),
	m_camera_controller(m_camera),
	m_text_box_renderer(m_logic.text_box),
	m_inventory_renderer(m_logic.item_registry, m_logic.inventory),
	m_combat_renderer(m_logic.party, m_logic.combat),
	m_quest_log_renderer(m_logic.quest_log),
	m_dev_tools(m_game_facade, m_resource_system.sequence_manager, project_path)
{
	// FIXME - make the constructor smaller by injecting into member classes via their constructors

	// Project description
	Project_Description description = load_project_description(String{project_path});
	SG_INFO("Loaded project \"%s\"", description.name.data());
	SetWindowTitle(description.name.data());

	// Item registry
	Item_Registry_Loader item_registry_loader(m_resource_system.texture_manager);
	item_registry_loader.load(m_logic.item_registry, project_path);

	// UI
	GUI_Loader gui_loader(m_resource_system.font_manager);
	m_text_box_renderer.load(gui_loader, project_path);
	m_quest_log_renderer.load(gui_loader, project_path);

	// Savegame location
	m_map_saveloader.set_save_directory("savegame");
	m_sequence_saveloader.set_save_directory("savegame");
	m_game_saveloader.set_save_directory("savegame");

	// Set up main character profile
	m_logic.party.main_character() = m_resource_system.character_profile_manager.get(description.default_character.data(), false);

	// Load savegame
	m_game_saveloader.load();

	// FIXME - refactor?
	m_logic.start_sequence = &m_resource_system.sequence_manager.get(description.start_sequence.data(), false);
	m_logic.start_sequence->try_activate();
}

Game::~Game()
{
	m_game_facade.save_game();
}

void Game::draw_frame(float time_delta)
{
	// FIXME - refactor this function
	if (IsKeyPressed(KEY_F3))
		m_dev_mode = !m_dev_mode;

	if (m_dev_mode) {
		m_camera_controller.update(*m_logic.map, m_logic.get_player());
		assert(m_logic.map);
		m_map_renderer.draw(*m_logic.map, m_camera);
		m_dev_tools.draw(*m_logic.map);
		return;
	}

	m_music_player.update();
	m_logic.update(time_delta);

	if (!m_logic.in_combat) {
		// Normal mode
		process_normal_input();
		assert(m_logic.map);
		m_resource_system.sequence_manager.update(time_delta); // FIXME - somehow refactor this into game logic
		m_camera_controller.update(*m_logic.map, m_logic.get_player());
		m_map_renderer.draw(*m_logic.map, m_camera);
		m_text_box_renderer.draw();

		if (m_show_inventory) {
			m_inventory_renderer.draw();
		} else if (m_show_quest_log) {
			m_quest_log_renderer.draw();
		}
	} else {
		// Combat mode
		process_combat_input();
		m_combat_renderer.draw();
		m_combat_controller.draw();
	}
}

void Game::process_normal_input()
{
	if (IsKeyPressed(KEY_ENTER)) {
		if (m_logic.text_box.contains_message())
			m_logic.text_box.advance();
		else
			m_logic.player_interact();
	} else if (IsKeyPressed(KEY_I)) {
		m_show_inventory = !m_show_inventory;
	} else if (IsKeyPressed(KEY_Q)) {
		m_show_quest_log = !m_show_quest_log;
	}

	if (IsKeyDown(KEY_UP)) {
		m_logic.move_player(Direction::up);
	} else if (IsKeyDown(KEY_DOWN)) {
		m_logic.move_player(Direction::down);
	} else if (IsKeyDown(KEY_RIGHT)) {
		m_logic.move_player(Direction::right);
	} else if (IsKeyDown(KEY_LEFT)) {
		m_logic.move_player(Direction::left);
	}
}

void Game::process_combat_input()
{
	if (IsKeyPressed(KEY_UP)) {
		m_combat_controller.go_up();
	} else if (IsKeyPressed(KEY_DOWN)) {
		m_combat_controller.go_down();
	} else if (IsKeyPressed(KEY_ENTER)) {
		m_combat_controller.enter();
	}
}
