#pragma once

#include "utils/vec2.hpp"
#include "combat/combat.hpp"

class Party;
class Combat;
class Combat_Unit;

struct Combat_Renderer_Unit
{
	float hp_shown_old;
	float hp_shown_current;
};

class Combat_Renderer : public Combat_Observer
{
public:
	Combat_Renderer(const Party&, Combat&);
	void draw(float dt);

private:
	void draw_party(float dt);
	void draw_enemies(float dt);
	void draw_hp_bar(const Vec2i unit_pos, const int unit_size, const Combat_Unit&, Combat_Renderer_Unit&, float dt);

	void on_hero_ability_selecting_begin() override {};
	void on_battle_begin() override;

	Array<Combat_Renderer_Unit> m_heroes;
	Array<Combat_Renderer_Unit> m_enemies;

	const Party& m_party;
	const Combat& m_combat;
};
