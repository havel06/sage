#pragma once

#include "character_profile.hpp"
#include "game_facade.hpp"
#include "map/map.hpp"
#include "item/inventory.hpp"
#include "item/item_registry.hpp"
#include "text_box.hpp"

// fwd
class Sequence;
class Resource_Manager;
class Music_Player;

class Game_Logic
{
public:
	Map map; // TODO - shouldn't map be private?
	Text_Box text_box; // TODO - shouldn't this be private?
	Character_Profile main_character; // TODO - make private?
	Item_Registry item_registry;
	Inventory inventory;
	Sequence* start_sequence = nullptr;
	bool player_actions_disabled = false;

	void update(float time_delta);
	Entity& get_player();
	void player_interact();
	void move_player(Direction direction);
private:
};
