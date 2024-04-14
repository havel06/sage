#include "game.hpp"
#include <raylib/raylib.h>

Game::Game(const char* project_path) :
	m_res_manager(project_path)
{
}

void Game::draw_frame(float time_delta)
{
	(void)time_delta;
	m_map_renderer.draw(m_map);
}
