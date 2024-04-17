#pragma once

#include "game_facade.hpp"
#include "map/map.hpp"
#include "item/inventory.hpp"
#include "item/item_registry.hpp"
#include "text_box.hpp"

// fwd
class Sequence;
class Resource_Manager;

class Game_Logic
{
public:
	Map map; // TODO - shouldn't map be private?
	Text_Box text_box; // TODO - shouldn't this be private?
	Item_Registry item_registry;
	Inventory inventory;
	Sequence* start_sequence = nullptr;

	void update(Resource_Manager&, float time_delta);
	Entity& get_player();
	void player_interact();
	// TODO - a single function in the API?
	void move_player_right();
	void move_player_left();
	void move_player_up();
	void move_player_down();
private:
	void move_player(Vec2i direction);
};
