#include "position.hpp"
#include "map.hpp"
#include "map/entity.hpp"

Vec2f Position::resolve(Map_Entities& entities) const
{
	if (entity_name.has_value()) {
		Entity* entity = entities.get_entity(entity_name.value());
		if (entity) {
			return entity->get_subgrid_position() + offset;
		} else {
			return offset;
		}
	} else {
		return offset;
	}
}
