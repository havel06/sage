#include "game.hpp"
#include "game_facade.hpp"
#include "io/item_registry_loader.hpp"
#include "io/project_loader.hpp"
#include "sequence/event.hpp"
#include "utils/log.hpp"
#include <raylib/raylib.h>

Game::Game(const char* project_path) :
	m_res_manager(project_path),
	m_text_box_renderer(m_logic.text_box),
	m_inventory_renderer(m_logic.item_registry, m_logic.inventory)
{
	// Project description
	Project_Description description = load_project_description(String{project_path});
	SG_INFO("Loaded project \"%s\"", description.name.data());
	SetWindowTitle(description.name.data());

	// Item registry
	Item_Registry_Loader item_registry_loader(m_res_manager);
	item_registry_loader.load(m_logic.item_registry, project_path);

	// FIXME - refactor?
	m_logic.start_sequence = &m_res_manager.get_sequence(description.start_sequence.data());
	m_logic.start_sequence->activate();
}

void Game::draw_frame(float time_delta)
{
	process_input();
	m_logic.update(m_res_manager, time_delta);
	m_camera.position = m_logic.get_player().get_subgrid_position() + Vec2f{0.5, 0.5};
	m_map_renderer.draw(m_logic.map, m_camera);
	m_text_box_renderer.draw();

	if (m_show_inventory) {
		m_inventory_renderer.draw();
	}
}

void Game::process_input()
{
	if (IsKeyPressed(KEY_ENTER)) {
		m_logic.text_box.advance();
		m_logic.player_interact();
	} else if (IsKeyPressed(KEY_I)) {
		m_show_inventory = !m_show_inventory;
	}

	if (IsKeyDown(KEY_UP)) {
		m_logic.move_player_up();
	} else if (IsKeyDown(KEY_DOWN)) {
		m_logic.move_player_down();
	} else if (IsKeyDown(KEY_RIGHT)) {
		m_logic.move_player_right();
	} else if (IsKeyDown(KEY_LEFT)) {
		m_logic.move_player_left();
	}
}
