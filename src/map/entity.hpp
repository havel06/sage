#pragma once

#include "graphics/sprite.hpp"
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
	void move(Vec2i direction);
	void look(Vec2i direction);
	Recti get_bounding_box() const;
	Vec2i get_look_direction() const { return m_look_direction; };
private:
	bool m_moving = false;
	Vec2f m_subgrid_offset = {0, 0};
	Vec2i m_look_direction = {0, 1}; // FIXME - handle invariant in a better way
};
