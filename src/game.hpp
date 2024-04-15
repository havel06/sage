#pragma once

#include "graphics/map_renderer.hpp"
#include "io/resource_manager.hpp"
#include "map/map.hpp"
#include "sequence/sequence.hpp"
#include "graphics/camera.hpp"
#include "game_logic.hpp"

class Game
{
public:
	Game(const char* project_path);
	void draw_frame(float time_delta);
private:
	void process_input();

	Resource_Manager m_res_manager;
	Game_Logic m_logic;
	Map_Renderer m_map_renderer;
	Game_Camera m_camera;
};
