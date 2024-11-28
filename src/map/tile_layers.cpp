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

Tile_Layer& Tile_Layers::get_layer(int index)
{
	// Const-cast abuse
	return (Tile_Layer&)(((const Tile_Layers*)this)->get_layer(index));
}

Tile_Layer* Tile_Layers::find_layer(const String& name)
{
	for (Tile_Layer& layer : m_layers) {
		if (layer.get_name() == name) {
			return &layer;
		}
	}

	return nullptr;
}

bool Tile_Layers::is_passable(Vec2i position) const
{
	if (!is_position_valid(position))
		return false;

	for (int i = 0; i < m_layers.size(); i++) {
		if (!m_layers[i].get_tile(position).passable) {
			return false;
		}
	}

	return true;
}

bool Tile_Layers::is_position_valid(Vec2i pos) const
{
	return (pos.x >= 0 && pos.x < m_width && pos.y >= 0 && pos.y < m_height);
}
