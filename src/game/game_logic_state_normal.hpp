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
class Map_Saveloader;

class Game_Logic_State_Normal
{
public:
	Text_Box text_box; // TODO - shouldn't this be private?
	Party party; // TODO - make private?
	Item_Registry item_registry;
	Inventory inventory;
	Quest_Log quest_log;
	bool player_actions_disabled = false;

	Game_Logic_State_Normal(Sequence_Manager&, Map_Saveloader&, Map_Manager&, const String& start_sequence);

	Map& get_map(); // FIXME - should this be here?
	void set_current_map(const String& filename);
	void update(float time_delta); // Should only be called by Game_Logic
	Entity& get_player();
	void player_interact();
	void move_player(Direction direction);
private:
	void spawn_player();

	Sequence_Manager& m_sequence_manager;
	Map_Saveloader& m_map_saveloader;
	Map_Manager& m_map_manager;

	String m_start_sequence;
	Map* m_map = nullptr;
	Map m_empty_map;
};
