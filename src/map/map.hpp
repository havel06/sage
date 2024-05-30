#pragma once

#include "utils/array.hpp"
#include "tile_layer.hpp"
#include "tile_layers.hpp"
#include "entity.hpp"
#include "utils/own_ptr.hpp"

class Map_Entities
{
public:
	Map_Entities() = default;
	Map_Entities(const Map_Entities&);
	Map_Entities& operator=(const Map_Entities&);

	void add_entity(Entity&&);
	int get_entity_count() const { return m_entities.size(); }
	Entity& get_entity(int index);
	const Entity& get_entity(int index) const;
	Entity* get_entity(const String& name);
	Entity* get_entity(Vec2i position);
private:
	Array<Own_Ptr<Entity>> m_entities;
};

class Map
{
public:
	Sequence* assigned_sequence = nullptr;
	Tile_Layers layers;
	Map_Entities entities;

	Map(const String& path, int width, int height);
	Map();

	void resize(int width, int height);

	int get_width() const { return m_width; }
	int get_height() const { return m_height; }
	bool is_position_valid(Vec2i pos) const;

	void set_path(const String& path) { m_path = path; }
	const String& get_path() const { return m_path; }
private:
	String m_path;

	int m_width;
	int m_height;
};
