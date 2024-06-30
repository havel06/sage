#pragma once

#include "character_profile.hpp"
#include "game_facade.hpp"
#include "map/map.hpp"
#include "item/inventory.hpp"
#include "item/item_registry.hpp"
#include "party.hpp"
#include "text_box.hpp"
#include "quest/quest_log.hpp"

// fwd
class Sequence;
class Resource_Manager_old;
class Music_Player;

class Game_Logic_State_Normal
{
public:
	Map* map = nullptr; // TODO - shouldn't map be private?
	Text_Box text_box; // TODO - shouldn't this be private?
	Party party; // TODO - make private?
	Item_Registry item_registry;
	Inventory inventory;
	Sequence* start_sequence = nullptr;
	Quest_Log quest_log;
	bool player_actions_disabled = false;

	Game_Logic_State_Normal();

	void update(float time_delta); // Should only be called by Game_Logic
	Entity& get_player();
	void player_interact();
	void move_player(Direction direction);
private:

	Map m_empty_map;
};
