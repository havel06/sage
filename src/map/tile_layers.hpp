#pragma once

#include "tile_layer.hpp"

class Tile_Layers
{
public:
	Tile_Layers(int width, int height);

	void resize(int width, int height);

	void add_layer(Tile_Layer&&);
	int get_layer_count() const { return m_layers.size(); }
	const Tile_Layer& get_layer(int index) const;

	bool is_empty() const { return m_layers.empty(); }
	bool is_passable(Vec2i) const;
private:
	int m_width = 0;
	int m_height = 0;
	Array<Tile_Layer> m_layers;
};
