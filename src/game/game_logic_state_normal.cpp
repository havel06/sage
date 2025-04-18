#include "game_logic_state_normal.hpp"
#include "combat/combat.hpp"
#include "map/entity.hpp"
#include "sequence/sequence.hpp"
#include "game_facade.hpp"
#include "utils/direction.hpp"
#include "utils/log.hpp"
#include "io/resource/sequence_manager.hpp"
#include "io/savegame/saveload_system.hpp"
#include "io/resource/map_manager.hpp"

Game_Logic_State_Normal::Game_Logic_State_Normal(Party& party, Sequence_Manager& seq_mgr, Saveload_System& saveload_system, Map_Manager& map_mgr) :
	inventory{item_registry},
	m_sequence_manager{seq_mgr},
	m_saveloader{saveload_system},
	m_map_manager{map_mgr},
	m_party{party}
{
	spawn_player();
}

void Game_Logic_State_Normal::update(Passkey<Game_Logic>, float time_delta)
{
	text_box.update(time_delta);
	
	Entity& player = get_player();
	Map& map = get_map();

	// Update map layers and entities
	// NOTE - entities must be updated before Area triggers are checked and sequences are updated,
	// so that the area triggers get triggered in the same frame where the entity has finished movement.
	map.update(time_delta);

	// Check area triggers
	for (int i = 0; i < map.entities.get_entity_count(); i++) {
		Entity& entity = map.entities.get_entity(i);

		if (entity.area_trigger &&
			entity.assigned_sequence.has_value() &&
			entity.get_bounding_box().contains(player.position))
		{
			entity.assigned_sequence.value().get().try_activate();
		}

	}

	// Update sequences
	// NOTE - sequences are updated after area triggers,
	// so that newly triggered area triggers are processed in the same frame.
	m_sequence_manager.update(time_delta);
}

Map& Game_Logic_State_Normal::get_map()
{
	if (m_map.has_value())
		return m_map.value().get();
	else
		return m_empty_map;
}

String Game_Logic_State_Normal::get_map_filename()
{
	if (m_map.has_value())
		return m_map.value().get_path();
	else
		return "";
}

void Game_Logic_State_Normal::set_current_map(const String& filename)
{
	m_map = m_map_manager.get(filename, false);
	spawn_player();
	// NOTE - map loading has to happen here, because we need the player entity to be present.
	m_saveloader.load_map(m_map.value().get(), m_map.value().get_path()); // Load progress

	SG_INFO("Set current map to \"%s\"", filename.data());
}

void Game_Logic_State_Normal::spawn_player()
{
	Map& map = get_map();
	Resource_Handle<Character_Profile> character = m_party.main_character();

	// Check if player already exists
	if (map.entities.get_entity(character.get().name))
		return;

	Entity player;

	player.name = character.get().name;
	player.assigned_character = character;

	map.entities.add_entity((Entity&&)player);
}


Entity& Game_Logic_State_Normal::get_player()
{
	Entity* player_ptr = get_map().entities.get_entity(m_party.main_character().get().name);
	assert(player_ptr);
	return *player_ptr;
}

void Game_Logic_State_Normal::player_interact()
{
	if (player_actions_disabled)
		return;

	Entity& player = get_player();
	Vec2i target = player.position + direction_to_vec2i(player.get_look_direction());
	Entity* target_entity = get_map().entities.get_entity(target);

	if (!target_entity)
		return;

	if (!target_entity->assigned_sequence.has_value())
		return;

	if (target_entity->area_trigger) // Don't activate area triggers with manual interaction
		return;

	target_entity->assigned_sequence.value().get().try_activate();
}

void Game_Logic_State_Normal::move_player(Direction direction)
{
	if (player_actions_disabled)
		return;

	if (text_box.contains_message())
		return;

	Map& map = get_map();
	Entity& player = get_player();
	player.look(direction);
	auto new_pos = player.position + direction_to_vec2i(direction);

	// Check for collision
	if (!map.is_passable(new_pos))
		return;

	player.move(direction);
}
