#include "game_logic.hpp"
#include "map/entity.hpp"
#include "sequence/sequence.hpp"
#include "game_facade.hpp"
#include "utils/log.hpp"

void Game_Logic::update(float time_delta)
{
	assert(start_sequence);
	start_sequence->update(time_delta);

	for (int i = 0; i < map.get_entity_count(); i++) {
		Entity& entity = map.get_entity(i);
		entity.update(time_delta);
		if (entity.assigned_sequence)
			entity.assigned_sequence->update(time_delta);
	}
}

Entity& Game_Logic::get_player()
{
	Entity* player_ptr = map.get_entity("Player");
	assert(player_ptr);
	return *player_ptr;
}

void Game_Logic::player_interact()
{
	Entity& player = get_player();
	Vec2i target = player.position + player.get_look_direction();
	Entity* target_entity = map.get_entity(target);

	if (!target_entity)
		return;

	if (!target_entity->assigned_sequence)
		return;

	target_entity->assigned_sequence->try_activate();
}

void Game_Logic::move_player_right()
{
	move_player({1, 0});
}

void Game_Logic::move_player_left()
{
	move_player({-1, 0});
}

void Game_Logic::move_player_up()
{
	move_player({0, -1});
}

void Game_Logic::move_player_down()
{
	move_player({0, 1});
}

void Game_Logic::move_player(Vec2i direction)
{
	Entity& player = get_player();
	player.look(direction);
	auto new_pos = player.position + direction;

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
