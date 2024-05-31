#pragma once

#include "character_profile.hpp"
#include "game_facade.hpp"
#include "map/map.hpp"
#include "item/inventory.hpp"
#include "item/item_registry.hpp"
#include "party.hpp"
#include "text_box.hpp"
#include "combat.hpp"
#include "quest/quest_log.hpp"

// fwd
class Sequence;
class Resource_Manager_old;
class Music_Player;

class Game_Logic
{
public:
	Map* map = nullptr; // TODO - shouldn't map be private?
	Text_Box text_box; // TODO - shouldn't this be private?
	Party party; // TODO - make private?
	Item_Registry item_registry;
	Inventory inventory;
	Sequence* start_sequence = nullptr;
	Combat combat;
	Quest_Log quest_log;
	bool player_actions_disabled = false;
	bool in_combat = false;

	Game_Logic();

	void update(float time_delta);
	Entity& get_player();
	void player_interact();
	void move_player(Direction direction);
private:

	Map m_empty_map;
};
