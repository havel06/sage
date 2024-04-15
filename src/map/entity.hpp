#pragma once

#include "graphics/sprite.hpp"
#include "utils/string.hpp"
#include "utils/vec2.hpp"

class Sequence;

class Entity
{
public:
	const Sequence* assigned_sequence = nullptr;

	String name;
	Sprite sprite;
	Vec2i position = {0, 0};
	float move_speed = 4;

	Vec2f get_subgrid_position() const;
	void update(float time_delta);
	void move_to(Vec2i);
private:
	bool m_moving = false;
	Vec2f m_subgrid_offset = {0, 0};
	Vec2i m_target_position = {0, 0};
};
