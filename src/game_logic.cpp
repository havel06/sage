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
		map.get_entity(i).update(time_delta);
	}
}

Entity& Game_Logic::get_player()
{
	Entity* player_ptr = map.get_entity("Player");
	assert(player_ptr);
	return *player_ptr;
}

void Game_Logic::move_player_right()
{
	//SG_DEBUG("move right");
	Entity& player = get_player();
	player.move_to(player.position + Vec2i{1, 0});
}

void Game_Logic::move_player_left()
{
	Entity& player = get_player();
	player.move_to(player.position + Vec2i{-1, 0});
}

void Game_Logic::move_player_up()
{
	Entity& player = get_player();
	player.move_to(player.position + Vec2i{0, -1});
}

void Game_Logic::move_player_down()
{
	Entity& player = get_player();
	player.move_to(player.position + Vec2i{0, 1});
}
