#pragma once

#include "graphics/map_renderer.hpp"
#include "map/map.hpp"

class Game
{
public:
	Game();
	void draw_frame(float time_delta);

private:
	Map m_map;
	Map_Renderer m_map_renderer;
};
