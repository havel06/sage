#include "game.hpp"
#include <raylib/raylib.h>

Game::Game()
{
}

void Game::draw_frame(float time_delta)
{
	(void)time_delta;
	m_map_renderer.draw(m_map);
}
