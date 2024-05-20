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
	m_game_facade(m_res_manager, m_music_player, m_logic),
	m_sequence_loader(m_res_manager, m_game_facade),
	m_res_manager(m_sequence_loader, project_path),
	m_text_box_renderer(m_logic.text_box),
	m_inventory_renderer(m_logic.item_registry, m_logic.inventory),
	m_camera_controller(m_camera),
	m_combat_renderer(m_logic.party, m_logic.combat),
	m_quest_log_renderer(m_logic.quest_log),
	m_combat_controller(m_logic.combat)
{
	// Project description
	Project_Description description = load_project_description(String{project_path});
	SG_INFO("Loaded project \"%s\"", description.name.data());
	SetWindowTitle(description.name.data());

	// Item registry
	Item_Registry_Loader item_registry_loader(m_res_manager);
	item_registry_loader.load(m_logic.item_registry, project_path);

	// UI
	m_text_box_renderer.load(project_path);

	// Set up main character profile
	m_logic.party.main_character() = m_res_manager.get_character_profile(description.default_character.data());

	// FIXME - refactor?
	m_logic.start_sequence = &m_res_manager.get_sequence(description.start_sequence.data());
	m_logic.start_sequence->try_activate();
}

void Game::draw_frame(float time_delta)
{
	m_music_player.update();
	m_logic.update(time_delta);

	if (!m_logic.in_combat) {
		// Normal mode
		process_normal_input();
		m_res_manager.update_sequences(time_delta); // FIXME - somehow refactor this into game logic
		m_camera_controller.update(m_logic.map, m_logic.get_player());
		m_map_renderer.draw(m_logic.map, m_camera);
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
