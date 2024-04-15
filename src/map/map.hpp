#pragma once

#include "utils/array.hpp"
#include "tile_layer.hpp"

class Map
{
public:
	Map(int width, int height);
	Map();

	void resize(int width, int height);
	int get_width() const { return m_width; }
	int get_height() const { return m_height; }
	void add_layer(Tile_Layer&&);
	int get_layer_count() const { return m_layers.size(); }
	const Tile_Layer& get_layer(int index) const;
private:
	int m_width;
	int m_height;

	Array<Tile_Layer> m_layers;
};
