#include "game.hpp"
#include "game_facade.hpp"
#include "io/project_loader.hpp"
#include "sequence/event.hpp"
#include "utils/log.hpp"
#include <raylib/raylib.h>

Game::Game(const char* project_path) :
	m_res_manager(project_path)
{
	Project_Description description = load_project_description(String{project_path});
	SG_INFO("Loaded project \"%s\"", description.name.data());
	SetWindowTitle(description.name.data());

	m_start_sequence = &m_res_manager.get_sequence(description.start_sequence.data());
	m_start_sequence->activate();

	// FIXME - remove
	m_camera.position = {10, 10};
}

void Game::draw_frame(float time_delta)
{
	assert(m_start_sequence);
	Game_Facade facade{m_res_manager, m_map};
	m_start_sequence->update(facade, time_delta);

	m_map_renderer.draw(m_map, m_camera);
}
