#include "combat_renderer_unit.hpp"
#include "graphics/shader.hpp"
#include "combat/combat_unit.hpp"

Combat_Renderer_Unit::Combat_Renderer_Unit(Sage_Shader& shader, float hp_shown, const Battle_Unit_Placement& placement_) :
	m_shader{shader}
{
	m_hp_shown_current = hp_shown;
	m_hp_shown_old = hp_shown;
	placement = placement_;
}

void Combat_Renderer_Unit::draw(const Combat_Unit& combat_unit, bool selected, float dt)
{
	// FIXME - refactor

	Vec2i screen_size = {GetScreenWidth(), GetScreenHeight()};
	const int pos_x = placement.position_x.to_pixels(screen_size);
	const int pos_y = placement.position_y.to_pixels(screen_size);
	const int size_x = placement.size_x.to_pixels(screen_size);
	const int size_y = placement.size_y.to_pixels(screen_size);

	Rectf transform = Rectf{
		.position = Vec2f{(float)pos_x, (float)pos_y},
		.size = Vec2f{(float)size_x, (float)size_y}
	}.scale_from_center(combat_unit.character.get().sprite_scale);

	// Reset highlight time if unit is newly selected
	if (!m_selected && selected) {
		m_highlight_time = 0;
	}

	m_selected = selected;

	// Selection highlight
	Colour highlight_colour = {255, 255, 255, 0};
	if (selected) {
		const float blink_speed = 7;
		const float highlight_max = 0.7;
		highlight_colour.a = 255 * highlight_max * ((sin(m_highlight_time * blink_speed) + 1) / 2);
	}

	// Damage taken highlight
	const float damage_highlight_len = 0.5;
	if (m_time_since_damage_taken <= damage_highlight_len) {
		// y = cos(t * pi / 2 / T)
		const float effect_intensity = cos(m_time_since_damage_taken * (PI / 2) / damage_highlight_len);
		const float highlight_max = 0.7;
		highlight_colour = Colour{220, 40, 40, (unsigned char)(255 * highlight_max * effect_intensity)};
	}

	// Heal highlight
	const float heal_highlight_len = 0.8;
	if (m_time_since_heal <= heal_highlight_len) {
		// y = sin(t * pi / T)
		const float effect_intensity = sin(m_time_since_heal * PI / heal_highlight_len);
		const float highlight_max = 0.7;
		highlight_colour = Colour{40, 220, 40, (unsigned char)(255 * highlight_max * effect_intensity)};
	}

	m_time_since_damage_taken += dt;
	m_time_since_heal += dt;
	m_highlight_time += dt;


	m_shader.begin();
	m_shader.set_highlight(highlight_colour);
	get_sprite(combat_unit).draw(transform, dt);
	m_shader.end();

	draw_hp_bar({pos_x, pos_y}, Vec2i{size_x, size_y}, combat_unit, dt);
}

const Animated_Sprite& Combat_Renderer_Unit::get_sprite(const Combat_Unit& combat_unit)
{
	// Custom sprite
	if (!combat_unit.custom_sprite.is_null()) {
		return combat_unit.custom_sprite;
	}

	// Character sprite
	if (combat_unit.get_side() == Combat_Unit_Side::hero) {
		return combat_unit.character.get().sprite_right;
	} else {
		return combat_unit.character.get().sprite_left;
	}
}

void Combat_Renderer_Unit::draw_hp_bar(const Vec2i unit_pos, Vec2i unit_size, const Combat_Unit& unit, float dt)
{
	const int bar_x = unit_pos.x;
	const int bar_y = unit_pos.y + unit_size.y + 8;
	const int padding = 4;

	const int height = 14;
	DrawRectangle(bar_x, bar_y, unit_size.x, height, BLACK);

	float hp_portion_old = (float)m_hp_shown_old / unit.character.get().max_hp;
	float hp_portion_current = (float)m_hp_shown_current / unit.character.get().max_hp;

	// Update hp shown
	const float speed_old = 8;
	const float speed_current = 12;
	if (m_hp_shown_old > unit.get_hp()) {
		m_hp_shown_old -= speed_old * dt;
	}
	m_hp_shown_current += (unit.get_hp() - m_hp_shown_current) * dt * speed_current;

	DrawRectangle(bar_x + padding, bar_y + padding, (unit_size.x - 2*padding) * hp_portion_old, height - 2 * padding, ORANGE);
	DrawRectangle(bar_x + padding, bar_y + padding, (unit_size.x - 2*padding) * hp_portion_current, height - 2 * padding, RED);
}

void Combat_Renderer_Unit::begin_effect_damage_taken()
{
	m_time_since_damage_taken = 0;
}

void Combat_Renderer_Unit::begin_effect_heal()
{
	m_time_since_heal = 0;
}
