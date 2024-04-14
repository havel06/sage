#include "map.hpp"

Map::Map(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Map::add_layer(Tile_Layer&& layer)
{
	assert(m_width == layer.get_width());
	assert(m_height == layer.get_height());
	m_layers.push_back((Tile_Layer&&)layer);
}
