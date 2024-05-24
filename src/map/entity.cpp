#include "entity.hpp"
#include "utils/abs.hpp"
#include "utils/direction.hpp"
#include "utils/log.hpp"
#include <assert.h>

void Entity::update(float time_delta)
{
	if (m_moving) {
		auto get_move_speed = [this](){
			if (assigned_character.has_value())
				return assigned_character.value().move_speed;
			else
				return move_speed;
		};

		m_subgrid_offset += direction_to_vec2i(m_look_direction) * get_move_speed() * time_delta;

		if (abs(m_subgrid_offset.x) >= 1 || abs(m_subgrid_offset.y) >= 1) {
			position += m_subgrid_offset.round();
			m_subgrid_offset = {0, 0};
			m_moving = false;
		}
	}
}

Vec2f Entity::get_subgrid_position() const
{
	return position + m_subgrid_offset;
}

void Entity::move(Direction direction)
{
	if (m_moving)
		return;

	m_look_direction = direction;
	m_moving = true;
}

void Entity::look(Direction direction)
{
	if (m_moving)
		return;

	m_look_direction = direction;
}

Recti Entity::get_bounding_box() const
{
	return {
		.position = position,
		.size = size
	};
}
