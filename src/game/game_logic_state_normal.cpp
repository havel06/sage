#include "game_logic_state_normal.hpp"
#include "combat/combat.hpp"
#include "map/entity.hpp"
#include "sequence/sequence.hpp"
#include "game_facade.hpp"
#include "utils/direction.hpp"
#include "utils/log.hpp"

Game_Logic_State_Normal::Game_Logic_State_Normal()
{
	map = &m_empty_map;
}

void Game_Logic_State_Normal::update(float time_delta)
{
	text_box.update(time_delta);
	
	assert(start_sequence);
	start_sequence->update(time_delta);

	Entity& player = get_player();

	assert(map);
	for (int i = 0; i < map->entities.get_entity_count(); i++) {
		Entity& entity = map->entities.get_entity(i);
		entity.update(time_delta);

		// Area triggers
		if (entity.area_trigger &&
			entity.assigned_sequence &&
			entity.get_bounding_box().contains(player.position))
		{
			entity.assigned_sequence->try_activate();
		}
	}
}

Entity& Game_Logic_State_Normal::get_player()
{
	Entity* player_ptr = map->entities.get_entity(party.main_character().name);
	assert(player_ptr);
	return *player_ptr;
}

void Game_Logic_State_Normal::player_interact()
{
	if (player_actions_disabled)
		return;

	Entity& player = get_player();
	Vec2i target = player.position + direction_to_vec2i(player.get_look_direction());
	Entity* target_entity = map->entities.get_entity(target);

	if (!target_entity)
		return;

	if (!target_entity->assigned_sequence)
		return;

	if (target_entity->area_trigger) // Don't activate area triggers with manual interaction
		return;

	target_entity->assigned_sequence->try_activate();
}

void Game_Logic_State_Normal::move_player(Direction direction)
{
	if (player_actions_disabled)
		return;

	Entity& player = get_player();
	player.look(direction);
	auto new_pos = player.position + direction_to_vec2i(direction);

	assert(map);
	// Check for tile collision
	if (!map->is_position_valid(new_pos) || !map->layers.is_passable(new_pos))
		return;

	// Check for entity collision
	for (int i = 0; i < map->entities.get_entity_count(); i++) {
		const Entity& entity = map->entities.get_entity(i);
		if (!entity.passable && entity.get_bounding_box().contains(new_pos))
			return;
	}

	player.move(direction);
}
