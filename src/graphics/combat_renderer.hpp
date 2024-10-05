#pragma once

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
	UI::Size pos_x;
	UI::Size pos_y;
};

// FIXME - refactor (after refactoring Combat itself)
class Combat_Renderer : public Combat_Observer
{
public:
	Combat_Renderer(const Party&, Combat&, const Combat_Controller&);
	void draw(float dt);

private:
	void draw_background(float dt);
	void draw_party(float dt);
	void draw_enemies(float dt);
	void draw_hp_bar(const Vec2i unit_pos, const int unit_size, const Combat_Unit&, Combat_Renderer_Unit&, float dt);

	void update_unit_position(int index, Combat_Renderer_Unit&, bool is_enemy, float dt);
	UI::Size get_hero_position_y(int index);
	UI::Size get_enemy_position_y(int index);

	void on_hero_ability_selecting_begin() override {};
	void on_battle_begin() override;

	float m_highlight_time = 0;
	Animated_Sprite m_background;
	Table<int /*id*/, Combat_Renderer_Unit> m_heroes;
	Table<int /*id*/, Combat_Renderer_Unit> m_enemies;

	const Party& m_party;
	const Combat& m_combat;
	const Combat_Controller& m_combat_controller;
	Sage_Shader m_shader; // NOTE - if shader is ever used in an another location, it would be smarter to use DI
};
