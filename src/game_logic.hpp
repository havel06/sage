#pragma once

#include "game_facade.hpp"
#include "map/map.hpp"

// fwd
class Sequence;
class Resource_Manager;

class Game_Logic
{
public:
	Map map; // TODO - shouldn't map be private?
	Sequence* start_sequence = nullptr;

	void update(Resource_Manager&, float time_delta);
	Entity& get_player();
	void player_interact();
	void move_player_right();
	void move_player_left();
	void move_player_up();
	void move_player_down();
private:
	void move_player(Vec2i offset);
};
