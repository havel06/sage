#pragma once

#include "utils/array.hpp"
#include "tile_layer.hpp"

class Map
{
public:
	Map(int width, int height);
	void add_layer(Tile_Layer&&);
private:
	int m_width;
	int m_height;

	Array<Tile_Layer> m_layers;
};
