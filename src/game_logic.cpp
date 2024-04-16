#include "game_logic.hpp"
#include "map/entity.hpp"
#include "sequence/sequence.hpp"
#include "game_facade.hpp"
#include "utils/log.hpp"

void Game_Logic::update(Resource_Manager& res_mgr, float time_delta)
{
	Game_Facade facade{res_mgr, *this};
	assert(start_sequence);
	start_sequence->update(facade, time_delta);

	for (int i = 0; i < map.get_entity_count(); i++) {
		Entity& entity = map.get_entity(i);
		entity.update(time_delta);
		if (entity.assigned_sequence)
			entity.assigned_sequence->update(facade, time_delta);
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

	target_entity->assigned_sequence->activate();
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

void Game_Logic::move_player(Vec2i offset)
{
	Entity& player = get_player();
	auto new_pos = player.position + offset;
	if (map.is_position_valid(new_pos) && map.layers.is_passable(new_pos)) {
		player.move_to(new_pos);
	}
}
