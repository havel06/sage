#include "map.hpp"

Map::Map(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Map::resize(int width, int height)
{
	assert(m_layers.empty());

	m_width = width;
	m_height = height;
}

Map::Map() : Map(0, 0)
{
}

void Map::add_layer(Tile_Layer&& layer)
{
	assert(m_width == layer.get_width());
	assert(m_height == layer.get_height());
	m_layers.push_back((Tile_Layer&&)layer);
}

const Tile_Layer& Map::get_layer(int index) const
{
	assert(index >= 0);
	assert(index < m_layers.size());
	return m_layers[index];
}
