#pragma once

#include "combat/battle_desc.hpp"
#include "graphics/animated_sprite.hpp"
#include "utils/vec2.hpp"
#include "combat/combat.hpp"
#include "ui/size.hpp"
#include "shader.hpp"

class Party;
class Combat;
class Combat_Unit;
class Combat_Controller;

// FIXME - encapsulate, refactor
struct Combat_Renderer_Unit
{
	float hp_shown_old;
	float hp_shown_current;
	Battle_Unit_Placement placement;
	float time_since_damage_taken = 10000;
	float time_since_heal = 10000;
};

// FIXME - refactor (after refactoring Combat itself)
class Combat_Renderer : public Combat_Observer
{
public:
	Combat_Renderer(Combat&, const Combat_Controller&);
	void draw(float dt);

private:
	void draw_background(float dt);
	void draw_party(float dt);
	void draw_enemies(float dt);
	void draw_hp_bar(const Vec2i unit_pos, Vec2i unit_size, const Combat_Unit&, Combat_Renderer_Unit&, float dt);

	void update_unit_position(int index, Combat_Renderer_Unit&, bool enemy, float dt);
	Battle_Unit_Placement get_enemy_unit_placement(int index);
	Battle_Unit_Placement get_hero_unit_placement(int index);

	void on_hero_ability_selecting_begin() override {};
	void on_battle_begin() override;
	void on_unit_hp_change(int id, int amount) override;

	float m_highlight_time = 0;
	int m_last_highlight_target = 0;
	Table<int /*id*/, Combat_Renderer_Unit> m_units;

	const Combat& m_combat;
	const Combat_Controller& m_combat_controller;
	Sage_Shader m_shader; // NOTE - if shader is ever used in an another location, it would be smarter to use DI
};
