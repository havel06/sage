#pragma once

#include "character_profile.hpp"
#include "game_facade.hpp"
#include "map/map.hpp"
#include "item/inventory.hpp"
#include "item/item_registry.hpp"
#include "party.hpp"
#include "text_box.hpp"
#include "quest/quest_log.hpp"
#include "io/resource/resource_handle.hpp"
#include "utils/optional.hpp"

// fwd
class Sequence;
class Resource_Manager_old;
class Music_Player;
class Map_Saveloader;

class Game_Logic_State_Normal
{
public:
	Text_Box text_box;
	Item_Registry item_registry;
	Inventory inventory;
	Quest_Log quest_log;
	bool player_actions_disabled = false;

	Game_Logic_State_Normal(Party&, Sequence_Manager&, Map_Saveloader&, Map_Manager&);

	Map& get_map(); // FIXME - should this be here?
	String get_map_filename(); // FIXME - should this be here?
	void set_current_map(const String& filename);
	void update(Passkey<Game_Logic>, float time_delta); // Should only be called by Game_Logic
	Entity& get_player();
	void player_interact();
	void move_player(Direction direction);
private:
	void spawn_player();

	Sequence_Manager& m_sequence_manager;
	Map_Saveloader& m_map_saveloader;
	Map_Manager& m_map_manager;
	Party& m_party;

	Optional<Resource_Handle<Map>> m_map;
	Map m_empty_map; // Used as default map
};
