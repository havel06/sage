#pragma once

#include "combat_renderer_unit.hpp"
#include "combat/battle_desc.hpp"
#include "graphics/animated_sprite.hpp"
#include "utils/vec2.hpp"
#include "combat/combat.hpp"
#include "../game_ui/size.hpp"
#include "../shader.hpp"

class Party;
class Combat;
class Combat_Unit;
class Combat_Controller;

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
	void draw_unit(const Combat_Unit&, int index, bool selected, float dt);

	void update_unit_position(int index, Combat_Renderer_Unit&, Combat_Unit_Side, float dt);
	Battle_Unit_Placement get_enemy_unit_placement(int index);
	Battle_Unit_Placement get_hero_unit_placement(int index);

	void on_hero_ability_selecting_begin() override {};
	void on_battle_begin() override;
	void on_unit_hp_change(int id, int amount) override;

	const Combat& m_combat;
	const Combat_Controller& m_combat_controller;

	Table<int /*id*/, Combat_Renderer_Unit> m_units;
	Sage_Shader m_shader; // NOTE - if shader is ever used in an another location, it would be smarter to use DI
};
