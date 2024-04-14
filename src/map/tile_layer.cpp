#include "tile_layer.hpp"


Tile_Layer::Tile_Layer(int width, int height)
{
	m_width = width;
	m_height = height;
	m_tiles.resize(width * height);
}

void Tile_Layer::set_tile(Vec2i position, const Tile& tile)
{
	assert(is_position_valid(position));
	m_tiles[position.y * m_width + position.x] = tile;
}

const Tile& Tile_Layer::get_tile(Vec2i position, const Tile&) const
{
	assert(is_position_valid(position));
	return m_tiles[position.y * m_width + position.x];
}

bool Tile_Layer::is_position_valid(Vec2i pos) const
{
	return (pos.x >= 0 && pos.x < m_width && pos.y >= 0 && pos.y < m_height);
}
