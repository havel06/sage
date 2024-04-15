#include "tile_layers.hpp"

Tile_Layers::Tile_Layers(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Tile_Layers::resize(int width, int height)
{
	assert(m_layers.empty());

	m_width = width;
	m_height = height;
}

void Tile_Layers::add_layer(Tile_Layer&& layer)
{
	assert(m_width == layer.get_width());
	assert(m_height == layer.get_height());

	m_layers.push_back((Tile_Layer&&)layer);
}

const Tile_Layer& Tile_Layers::get_layer(int index) const
{
	assert(index >= 0);
	assert(index < m_layers.size());
	return m_layers[index];
}

bool Tile_Layers::is_passable(Vec2i position) const
{
	for (int i = 0; i < m_layers.size(); i++) {
		if (!m_layers[i].get_tile(position).passable) {
			return false;
		}
	}

	return true;
}
