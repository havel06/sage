#include "map_renderer.hpp"
#include "character_profile.hpp"
#include "graphics/camera.hpp"
#include "map/map.hpp"
#include "map/entity.hpp"
#include "raylib/raylib.h"
#include "sprite.hpp"
#include "utils/direction.hpp"
#include "utils/log.hpp"
#include "utils/minmax.hpp"

void Map_Renderer::draw(const Map& map, const Game_Camera& camera, float dt)
{
	BeginMode2D(camera.to_ray_cam());

	for (int i = 0; i < map.layers.get_layer_count(); i++) {
		draw_layer(map.layers.get_layer(i), camera, dt);
	}

	for (int i = 0; i < map.entities.get_entity_count(); i++) {
		draw_entity(map.entities.get_entity(i), dt);
	}

	EndMode2D();
}

void Map_Renderer::draw_layer(const Tile_Layer& layer, const Game_Camera& camera, float time_delta)
{
	// Optimization - only draw the tiles that are visible by the camera
	const Rectf frustrum = camera.get_frustrum();
	const int min_x = max(frustrum.position.x, 0.0f);
	const int min_y = max(frustrum.position.y, 0.0f);
	const int max_x = min(frustrum.position.x + frustrum.size.x, layer.get_width() - 1);
	const int max_y = min(frustrum.position.y + frustrum.size.y, layer.get_height() - 1);

	for (int y = min_y; y <= max_y; y++) {
		for (int x = min_x; x <= max_x; x++) {
			draw_tile(layer.get_tile({x, y}), {x, y}, time_delta);
		}
	}
}

void Map_Renderer::draw_tile(const Tile& tile, Vec2i position, float time_delta)
{
	Rectf transform = Rectf{
		.position = position,
		.size = {1, 1}
	};

	tile.sprite.draw(transform, time_delta);
}

void Map_Renderer::draw_entity(const Entity& entity, float time_delta)
{
	Rectf transform = Rectf{
		.position = entity.get_subgrid_position(),
		.size = entity.size
	};

	Direction look_direction = entity.get_look_direction();

	if (entity.assigned_character.has_value()) {
		const Character_Profile& character = entity.assigned_character.value().get();

		transform.size = character.size;
		transform.position.y -= character.size.y - 1; //Adjust foot position

		if (entity.is_moving()) {
			switch (look_direction) {
				case Direction::down:
					character.sprite_move_down.draw(transform, time_delta);
					break;
				case Direction::up:
					character.sprite_move_up.draw(transform, time_delta);
					break;
				case Direction::right:
					character.sprite_move_right.draw(transform, time_delta);
					break;
				case Direction::left:
					character.sprite_move_left.draw(transform, time_delta);
					break;
			}
		} else {
			switch (look_direction) {
				case Direction::down:
					character.sprite_down.draw(transform, time_delta);
					break;
				case Direction::up:
					character.sprite_up.draw(transform, time_delta);
					break;
				case Direction::right:
					character.sprite_right.draw(transform, time_delta);
					break;
				case Direction::left:
					character.sprite_left.draw(transform, time_delta);
					break;
			}
		}
	} else {
		entity.sprite.draw(transform, time_delta);
	}
}
