#pragma once

#include "utils/vec2.hpp"

// fwd
class Map;
class Tile_Layer;
struct Tile;

class Map_Renderer
{
public:
	void draw(const Map& map);
private:
	void draw_layer(const Tile_Layer& layer);
	void draw_tile(const Tile& tile, Vec2i position);
};
