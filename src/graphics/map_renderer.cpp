#include "map_renderer.hpp"
#include "character_profile.hpp"
#include "graphics/camera.hpp"
#include "map/map.hpp"
#include "map/entity.hpp"
#include "raylib/raylib.h"
#include "sprite.hpp"
#include "utils/direction.hpp"
#include "utils/log.hpp"

void Map_Renderer::draw(const Map& map, const Game_Camera& camera, float dt)
{
	BeginMode2D(camera.to_ray_cam());

	for (int i = 0; i < map.layers.get_layer_count(); i++) {
		draw_layer(map.layers.get_layer(i));
	}

	for (int i = 0; i < map.entities.get_entity_count(); i++) {
		draw_entity(map.entities.get_entity(i), dt);
	}

	EndMode2D();
}

void Map_Renderer::draw_layer(const Tile_Layer& layer)
{
	for (int y = 0; y < layer.get_height(); y++) {
		for (int x = 0; x < layer.get_width(); x++) {
			draw_tile(layer.get_tile({x, y}), {x, y});
		}
	}
}

void Map_Renderer::draw_tile(const Tile& tile, Vec2i position)
{
	Rectf transform = Rectf{
		.position = position,
		.size = {1, 1}
	};

	tile.sprite.draw(transform);
}

void Map_Renderer::draw_entity(const Entity& entity, float time_delta)
{
	Rectf transform = Rectf{
		.position = entity.get_subgrid_position(),
		.size = entity.size
	};

	Direction look_direction = entity.get_look_direction();

	if (entity.assigned_character.has_value()) {
		const Character_Profile& character = entity.assigned_character.value();

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
		entity.sprite.draw(transform);
	}
}
