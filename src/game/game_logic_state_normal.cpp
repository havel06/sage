#include "game_logic_state_normal.hpp"
#include "combat/combat.hpp"
#include "map/entity.hpp"
#include "sequence/sequence.hpp"
#include "game_facade.hpp"
#include "utils/direction.hpp"
#include "utils/log.hpp"
#include "io/resource/sequence_manager.hpp"
#include "io/savegame/map_saveloader.hpp"
#include "io/resource/map_manager.hpp"

Game_Logic_State_Normal::Game_Logic_State_Normal(Party& party, Sequence_Manager& seq_mgr, Map_Saveloader& map_saveloader, Map_Manager& map_mgr, const String& start_sequence) :
	m_sequence_manager{seq_mgr},
	m_map_saveloader{map_saveloader},
	m_map_manager{map_mgr},
	m_party{party}
{
	m_start_sequence = start_sequence;
	spawn_player();
}

void Game_Logic_State_Normal::update(float time_delta)
{
	// Activate starting sequence (NOTE - could be optimised)
	m_sequence_manager.get(m_start_sequence.data(), false).get().try_activate();

	text_box.update(time_delta);
	
	m_sequence_manager.update(time_delta);
	Entity& player = get_player();

	Map& map = get_map();
	for (int i = 0; i < map.entities.get_entity_count(); i++) {
		Entity& entity = map.entities.get_entity(i);
		entity.update(time_delta);

		// Area triggers
		if (entity.area_trigger &&
			entity.assigned_sequence.has_value() &&
			entity.get_bounding_box().contains(player.position))
		{
			entity.assigned_sequence.value().get().try_activate();
		}
	}
}

Map& Game_Logic_State_Normal::get_map()
{
	if (m_map.has_value())
		return m_map.value().get();
	else
		return m_empty_map;
}

void Game_Logic_State_Normal::set_current_map(const String& filename)
{
	m_map = m_map_manager.get(filename, false);
	spawn_player();
	// NOTE - map loading has to happen here, because we need the player entity to be present.
	m_map_saveloader.load(m_map.value().get()); // Load progress

	if (m_map.value().get().assigned_sequence.has_value())
		m_map.value().get().assigned_sequence.value().get().try_activate();

	SG_INFO("Set current map to \"%s\"", filename.data());
}

void Game_Logic_State_Normal::spawn_player()
{
	assert(m_map.has_value());
	Resource_Handle<Character_Profile> character = m_party.main_character();

	// Check if player already exists
	if (m_map.value().get().entities.get_entity(character.get().name))
		return;

	Entity player;

	player.name = character.get().name;
	player.assigned_character = character;

	m_map.value().get().entities.add_entity((Entity&&)player);
}


Entity& Game_Logic_State_Normal::get_player()
{
	Entity* player_ptr = m_map.value().get().entities.get_entity(m_party.main_character().get().name);
	assert(player_ptr);
	return *player_ptr;
}

void Game_Logic_State_Normal::player_interact()
{
	if (player_actions_disabled)
		return;

	Entity& player = get_player();
	Vec2i target = player.position + direction_to_vec2i(player.get_look_direction());
	Entity* target_entity = m_map.value().get().entities.get_entity(target);

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

	Entity& player = get_player();
	player.look(direction);
	auto new_pos = player.position + direction_to_vec2i(direction);

	assert(m_map.has_value());
	// Check for tile collision
	if (!m_map.value().get().is_position_valid(new_pos) || !m_map.value().get().layers.is_passable(new_pos))
		return;

	// Check for entity collision
	for (int i = 0; i < m_map.value().get().entities.get_entity_count(); i++) {
		const Entity& entity = m_map.value().get().entities.get_entity(i);
		if (!entity.passable && entity.get_bounding_box().contains(new_pos))
			return;
	}

	player.move(direction);
}
