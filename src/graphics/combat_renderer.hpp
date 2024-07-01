#pragma once

#include "utils/vec2.hpp"

class Party;
class Combat;
class Combat_Unit;

class Combat_Renderer
{
public:
	Combat_Renderer(const Party&, const Combat&);
	void draw(float dt);

private:
	void draw_party(float dt);
	void draw_enemies(float dt);
	void draw_hp_bar(const Vec2i unit_pos, const int unit_size, const Combat_Unit&);

	const Party& m_party;
	const Combat& m_combat;
};
