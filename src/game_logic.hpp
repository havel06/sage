#pragma once

#include "map/map.hpp"

// fwd
class Sequence;
class Resource_Manager;

class Game_Logic
{
public:
	Map map;
	Sequence* start_sequence = nullptr;

	void update(Resource_Manager&, float time_delta);
	Entity& get_player();
	void move_player_right();
	void move_player_left();
	void move_player_up();
	void move_player_down();
};
