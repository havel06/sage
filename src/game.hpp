#pragma once

#include "graphics/map_renderer.hpp"
#include "io/resource_manager.hpp"
#include "map/map.hpp"
#include "sequence/sequence.hpp"

class Game
{
public:
	Game(const char* project_path);
	void draw_frame(float time_delta);

private:
	Resource_Manager m_res_manager;
	Map m_map;
	Map_Renderer m_map_renderer;

	Sequence* m_start_sequence = nullptr;
};
