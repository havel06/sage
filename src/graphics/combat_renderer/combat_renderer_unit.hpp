#pragma once
#include "combat/battle_desc.hpp"
#include "graphics/animated_sprite.hpp"

// fwd
class Combat_Unit;
class Sage_Shader;

class Combat_Renderer_Unit
{
public:
	Battle_Unit_Placement placement;
	Combat_Renderer_Unit(Sage_Shader& shader, float hp_shown, const Battle_Unit_Placement&);

	float get_hp_shown() const { return m_hp_shown_current; }
	void draw(const Combat_Unit&, bool selected, float dt);
	void begin_effect_damage_taken();
	void begin_effect_heal();

private:
	void draw_hp_bar(const Vec2i unit_pos, Vec2i unit_size, const Combat_Unit&, float dt);
	const Animated_Sprite& get_sprite(const Combat_Unit&);

	float m_hp_shown_old = 0;
	float m_hp_shown_current = 0;
	float m_time_since_damage_taken = 10000;
	float m_time_since_heal = 10000;
	float m_highlight_time = 0;
	bool m_selected = false;

	Sage_Shader& m_shader;
};
