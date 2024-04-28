#include "game_logic.hpp"
#include "combat.hpp"
#include "map/entity.hpp"
#include "sequence/sequence.hpp"
#include "game_facade.hpp"
#include "utils/direction.hpp"
#include "utils/log.hpp"

Game_Logic::Game_Logic() :
	combat(party)
{
}

void Game_Logic::update(float time_delta)
{
	if (in_combat) {
		// Combat mode
		combat.update();
		Combat_Result result = combat.get_current_result();
		if (result == Combat_Result::won || result == Combat_Result::lost) {
			in_combat = false;
		}
	} else {
		// Normal mode
		assert(start_sequence);
		start_sequence->update(time_delta);

		for (int i = 0; i < map.get_entity_count(); i++) {
			Entity& entity = map.get_entity(i);
			entity.update(time_delta);
		}
	}
}

Entity& Game_Logic::get_player()
{
	Entity* player_ptr = map.get_entity(party.main_character().name);
	assert(player_ptr);
	return *player_ptr;
}

void Game_Logic::player_interact()
{
	if (player_actions_disabled)
		return;

	Entity& player = get_player();
	Vec2i target = player.position + direction_to_vec2i(player.get_look_direction());
	Entity* target_entity = map.get_entity(target);

	if (!target_entity)
		return;

	if (!target_entity->assigned_sequence)
		return;

	target_entity->assigned_sequence->try_activate();
}

void Game_Logic::move_player(Direction direction)
{
	if (player_actions_disabled)
		return;

	Entity& player = get_player();
	player.look(direction);
	auto new_pos = player.position + direction_to_vec2i(direction);

	// Check for tile collision
	if (!map.is_position_valid(new_pos) || !map.layers.is_passable(new_pos))
		return;

	// Check for entity collision
	for (int i = 0; i < map.get_entity_count(); i++) {
		const Entity& entity = map.get_entity(i);
		if (!entity.passable && entity.get_bounding_box().contains(new_pos))
			return;
	}

	player.move(direction);
}
