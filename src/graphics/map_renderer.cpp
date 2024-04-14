#include "map_renderer.hpp"
#include "map/map.hpp"
#include "sprite.hpp"

void Map_Renderer::draw(const Map& map)
{
	for (int i = 0; i < map.get_layer_count(); i++) {
		draw_layer(map.get_layer(i));
	}
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
	assert(tile.sprite);

	tile.sprite->draw(Rectf{
		.position = position,
		.size = {1, 1}
	});
}
