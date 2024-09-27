#pragma once

#include "graphics/animated_sprite.hpp"
#include "utils/vec2.hpp"
#include "combat/combat.hpp"
#include "ui/size.hpp"

class Party;
class Combat;
class Combat_Unit;

struct Combat_Renderer_Unit
{
	float hp_shown_old;
	float hp_shown_current;
	UI::Size pos_x;
	UI::Size pos_y;
};

class Combat_Renderer : public Combat_Observer
{
public:
	Combat_Renderer(const Party&, Combat&);
	void draw(float dt);

private:
	void draw_background(float dt);
	void draw_party(float dt);
	void draw_enemies(float dt);
	void draw_hp_bar(const Vec2i unit_pos, const int unit_size, const Combat_Unit&, Combat_Renderer_Unit&, float dt);

	void on_hero_ability_selecting_begin() override {};
	void on_battle_begin() override;

	Animated_Sprite m_background;
	Array<Combat_Renderer_Unit> m_heroes;
	Array<Combat_Renderer_Unit> m_enemies;

	const Party& m_party;
	const Combat& m_combat;
};
