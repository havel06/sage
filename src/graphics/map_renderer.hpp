#pragma once

#include "utils/vec2.hpp"

// fwd
class Map;
class Tile_Layer;
class Game_Camera;
class Entity;
struct Tile;

class Map_Renderer
{
public:
	void draw(const Map& map, const Game_Camera&, float time_delta);
private:
	void draw_layer(const Tile_Layer& layer, const Game_Camera&);
	void draw_tile(const Tile& tile, Vec2i position);
	void draw_entity(const Entity&, float time_delta);
};
