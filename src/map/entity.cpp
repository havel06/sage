#include "entity.hpp"
#include "utils/abs.hpp"
#include "utils/log.hpp"
#include <assert.h>

void Entity::update(float time_delta)
{
	if (m_moving) {
		Vec2f direction = (m_target_position - position).normalised() * move_speed * time_delta;
		m_subgrid_offset += direction;

		if (abs(m_subgrid_offset.x) >= 1 || abs(m_subgrid_offset.y) >= 1) {
			position += m_subgrid_offset.round();
			m_subgrid_offset = {0, 0};
		}

		if (m_target_position == position) {
			m_moving = false;
		}
	}
}

Vec2f Entity::get_subgrid_position() const
{
	return position + m_subgrid_offset;
}

void Entity::move_to(Vec2i new_position)
{
	auto offset = new_position - this->position;
	assert(offset.x == 0 || offset.y == 0);

	if (m_moving)
		return;

	// Look direction
	m_look_direction = offset.normalised();

	m_moving = true;
	m_target_position = new_position;
}
