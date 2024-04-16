#pragma once

#include "utils/array.hpp"
#include "tile_layer.hpp"
#include "tile_layers.hpp"
#include "entity.hpp"

class Map
{
public:
	Tile_Layers layers;

	Map(int width, int height);
	Map();

	void resize(int width, int height);

	int get_width() const { return m_width; }
	int get_height() const { return m_height; }
	bool is_position_valid(Vec2i pos) const;

	void add_entity(Entity&&);
	int get_entity_count() const { return m_entities.size(); }
	Entity& get_entity(int index);
	const Entity& get_entity(int index) const;
	Entity* get_entity(const String& name);
	Entity* get_entity(Vec2i position);
private:
	int m_width;
	int m_height;

	Array<Entity> m_entities;
};
