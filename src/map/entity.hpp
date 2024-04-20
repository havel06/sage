#pragma once

#include "graphics/sprite.hpp"
#include "utils/direction.hpp"
#include "utils/string.hpp"
#include "utils/vec2.hpp"

class Sequence;

class Entity
{
public:
	Sequence* assigned_sequence = nullptr;

	String name;
	Sprite sprite;
	Vec2i position = {0, 0};
	Vec2i size = {1, 1};
	float move_speed = 4.5;
	bool passable = false;

	Vec2f get_subgrid_position() const;
	void update(float time_delta);
	void move(Direction);
	void look(Direction);
	Recti get_bounding_box() const;
	Direction get_look_direction() const { return m_look_direction; };
private:
	bool m_moving = false;
	Vec2f m_subgrid_offset = {0, 0};
	Direction m_look_direction = Direction::down;
};
