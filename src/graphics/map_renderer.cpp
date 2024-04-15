#include "map_renderer.hpp"
#include "map/map.hpp"
#include "raylib/raylib.h"
#include "sprite.hpp"
#include "utils/log.hpp"

void Map_Renderer::draw(const Map& map)
{
	Camera2D camera = {};
	camera.zoom = 32;

	BeginMode2D(camera);

	for (int i = 0; i < map.get_layer_count(); i++) {
		draw_layer(map.get_layer(i));
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
