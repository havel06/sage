#include "map.hpp"
#include "map/entity.hpp"
#include "utils/log.hpp"

Map_Entities::Map_Entities(const Map_Entities& other)
{
	for (int i = 0; i < other.get_entity_count(); i++) {
		const Entity& entity = other.get_entity(i);
		add_entity(Entity{entity});
	}
}

Map_Entities& Map_Entities::operator=(const Map_Entities& other)
{
	m_entities.clear();

	for (int i = 0; i < other.get_entity_count(); i++) {
		const Entity& entity = other.get_entity(i);
		add_entity(Entity{entity});
	}

	return *this;
}

Map::Map(int width, int height) :
	layers{width, height}
{
	m_width = width;
	m_height = height;
}

void Map::resize(int width, int height)
{
	assert(layers.is_empty());

	layers.resize(width, height);
	m_width = width;
	m_height = height;
}

bool Map::is_position_valid(Vec2i pos) const
{
	return (pos.x >= 0 && pos.x < m_width && pos.y >= 0 && pos.y < m_height);
}

Map::Map() : Map(0, 0)
{
}

void Map_Entities::add_entity(Entity&& entity)
{
	SG_DEBUG("Adding entity \"%s\"", entity.name.data());
	
	// Check for duplicated name
	for (const Own_Ptr<Entity>& e : m_entities) {
		if (e->name == entity.name) {
			SG_ERROR("Unable to add entity \"%s\" due to name duplication.", entity.name.data());
			return;
		}
	}

	m_entities.push_back((Entity&&)entity);
}

Entity& Map_Entities::get_entity(int index)
{
	return *m_entities[index];
}

const Entity& Map_Entities::get_entity(int index) const
{
	return *m_entities[index];
}

Entity* Map_Entities::get_entity(const String& name)
{
	for (auto& entity : m_entities) {
		if (entity->name == name) {
			return entity.get();
		}
	}

	return nullptr;
}

Entity* Map_Entities::get_entity(Vec2i position)
{
	for (int i = 0; i < m_entities.size(); i++) {
		if (m_entities[i]->get_bounding_box().contains(position)) {
			return m_entities[i].get();
		}
	}

	return nullptr;
}

bool Map::is_passable(Vec2i pos) const
{
	// Check for tile collision
	if (!is_position_valid(pos) || !layers.is_passable(pos))
		return false;

	// Check for entity collision
	for (int i = 0; i < entities.get_entity_count(); i++) {
		const Entity& entity = entities.get_entity(i);
		if (!entity.passable && entity.get_bounding_box().contains(pos))
			return false;
	}

	return true;
}

void Map::update(float dt)
{
	for (int i = 0; i < entities.get_entity_count(); i++) {
		entities.get_entity(i).update(dt);
	}
	
	for (int i = 0; i < layers.get_layer_count(); i++) {
		layers.get_layer(i).update(dt);
	}
}
