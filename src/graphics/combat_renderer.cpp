#include "combat_renderer.hpp"
#include "combat/battle_desc.hpp"
#include "combat/combat_controller.hpp"
#include "graphics/animated_sprite.hpp"
#include "party.hpp"
#include "utils/log.hpp"
#include "utils/rect.hpp"
#include "combat/combat.hpp"
#include "utils/vec2.hpp"
#include <raylib/raylib.h>

Combat_Renderer::Combat_Renderer(Combat& combat, const Combat_Controller& combat_controller) :
	m_combat{combat},
	m_combat_controller{combat_controller}
{
	combat.add_observer(*this);
}

void Combat_Renderer::draw(float dt)
{
	draw_background(dt);
	draw_party(dt);
	draw_enemies(dt);
	m_highlight_time += dt;
}

void Combat_Renderer::draw_background(float dt)
{
	// Render sprite to cover screen
	const float texture_size_x = m_background.get_current_frame().texture_clip.size.x;
	const float texture_size_y = m_background.get_current_frame().texture_clip.size.y;

	const float scale_x = GetScreenWidth() / texture_size_x;
	const float scale_y = GetScreenHeight() / texture_size_y;

	if (scale_x > scale_y) {
		// Sprite needs to stretch horizontally
		m_background.draw({{0, 0}, {texture_size_x * scale_x, texture_size_y * scale_x}}, dt);
	} else {
		// Sprite needs to stretch vertically
		m_background.draw({{0, 0}, {texture_size_x * scale_y, texture_size_y * scale_y}}, dt);
	}
}

void Combat_Renderer::draw_party(float dt)
{
	for (int i = 0; i < m_combat.get_hero_count(); i++) {
		const Combat_Unit& combat_unit = m_combat.get_hero(i);
		Combat_Renderer_Unit* renderer_unit = m_units.get(combat_unit.get_id());
		assert(renderer_unit);

		update_unit_position(i, *renderer_unit, false, dt);

		Vec2i screen_size = {GetScreenWidth(), GetScreenHeight()};
		const int pos_x = renderer_unit->placement.position_x.to_pixels(screen_size);
		const int pos_y = renderer_unit->placement.position_y.to_pixels(screen_size);
		const int size_x = renderer_unit->placement.size_x.to_pixels(screen_size);
		const int size_y = renderer_unit->placement.size_y.to_pixels(screen_size);

		Rectf transform = Rectf{
			.position = Vec2f{(float)pos_x, (float)pos_y},
			.size = Vec2f{(float)size_x, (float)size_y}
		}.scale_from_center(combat_unit.character.get().sprite_scale);

		// Selection highlight
		Colour highlight_colour = {255, 255, 255, 0};
		if (m_combat_controller.is_selecting_hero() &&
				m_combat_controller.get_current_selected_target() == i) {
			const float blink_speed = 7;
			const float highlight_max = 0.7;
			highlight_colour.a = highlight_max * ((sin(m_highlight_time * blink_speed) + 1) / 2);
		}

		// Damage taken highlight
		const float damage_highlight_len = 0.5;
		if (renderer_unit->time_since_damage_taken <= damage_highlight_len) {
			// y = cos(t * pi / 2 / T)
			const float effect_intensity = cos(renderer_unit->time_since_damage_taken * M_PI_2 / damage_highlight_len);
			const float highlight_max = 0.7;
			highlight_colour = Colour{220, 40, 40, (unsigned char)(255 * highlight_max * effect_intensity)};
		}

		// Heal highlight
		const float heal_highlight_len = 0.8;
		if (renderer_unit->time_since_heal <= heal_highlight_len) {
			// y = sin(t * pi / T)
			const float effect_intensity = sin(renderer_unit->time_since_heal * M_PI / heal_highlight_len);
			const float highlight_max = 0.7;
			highlight_colour = Colour{40, 220, 40, (unsigned char)(255 * highlight_max * effect_intensity)};
		}

		renderer_unit->time_since_damage_taken += dt;
		renderer_unit->time_since_heal += dt;

		const Animated_Sprite& sprite = combat_unit.custom_sprite.is_null() ?
				combat_unit.character.get().sprite_right :
				combat_unit.custom_sprite;

		m_shader.begin();
		m_shader.set_highlight(highlight_colour);
		sprite.draw(transform, dt);
		m_shader.end();

		draw_hp_bar({pos_x, pos_y}, Vec2i{size_x, size_y}, combat_unit, *renderer_unit, dt);
	}
}

void Combat_Renderer::draw_enemies(float dt)
{
	for (int i = 0; i < m_combat.get_enemy_count(); i++) {
		const Combat_Unit& combat_unit = m_combat.get_enemy(i);
		Combat_Renderer_Unit* renderer_unit = m_units.get(combat_unit.get_id());
		assert(renderer_unit);

		update_unit_position(i, *renderer_unit, true, dt);

		Vec2i screen_size = {GetScreenWidth(), GetScreenHeight()};
		const int pos_x = renderer_unit->placement.position_x.to_pixels(screen_size);
		const int pos_y = renderer_unit->placement.position_y.to_pixels(screen_size);
		const int size_x = renderer_unit->placement.size_x.to_pixels(screen_size);
		const int size_y = renderer_unit->placement.size_y.to_pixels(screen_size);

		Rectf transform = Rectf{
			.position = Vec2f{(float)pos_x, (float)pos_y},
			.size = Vec2f{(float)size_x, (float)size_y}
		}.scale_from_center(combat_unit.character.get().sprite_scale);

		// Selection highlight
		Colour highlight_colour = {255, 255, 255, 0};
		if (m_combat_controller.is_selecting_enemy() &&
				m_combat_controller.get_current_selected_target() == i) {
			const float blink_speed = 7;
			const float highlight_max = 0.7;
			// Reset highlight time if selecting a new enemy
			if (m_last_highlight_target != i) {
				m_last_highlight_target = i;
				m_highlight_time = 0;
			}
			highlight_colour.a = 255 * highlight_max * ((cos(m_highlight_time * blink_speed) + 1) / 2);
		}

		// Damage taken highlight
		const float damage_highlight_len = 0.5;
		if (renderer_unit->time_since_damage_taken <= damage_highlight_len) {
			// y = cos(t * pi / 2 / T)
			const float effect_intensity = cos(renderer_unit->time_since_damage_taken * M_PI_2 / damage_highlight_len);
			const float highlight_max = 0.7;
			highlight_colour = Colour{220, 40, 40, (unsigned char)(255 * highlight_max * effect_intensity)};
		}

		// Heal highlight
		const float heal_highlight_len = 0.7;
		if (renderer_unit->time_since_heal <= heal_highlight_len) {
			// y = cos(t * pi / 2 / T)
			const float effect_intensity = cos(renderer_unit->time_since_heal * M_PI_2 / heal_highlight_len);
			const float highlight_max = 0.7;
			highlight_colour = Colour{40, 220, 40, (unsigned char)(255 * highlight_max * effect_intensity)};
		}

		renderer_unit->time_since_damage_taken += dt;
		renderer_unit->time_since_heal += dt;

		const Animated_Sprite& sprite = combat_unit.custom_sprite.is_null() ?
				combat_unit.character.get().sprite_left :
				combat_unit.custom_sprite;

		m_shader.begin();
		m_shader.set_highlight(highlight_colour);
		sprite.draw(transform, dt);
		m_shader.end();

		draw_hp_bar({pos_x, pos_y}, Vec2i{size_x, size_y}, combat_unit, *renderer_unit, dt);
	}
}

void Combat_Renderer::draw_hp_bar(const Vec2i unit_pos, Vec2i unit_size, const Combat_Unit& unit, Combat_Renderer_Unit& renderer_unit, float dt)
{
	const int bar_x = unit_pos.x;
	const int bar_y = unit_pos.y + unit_size.y + 8;
	const int padding = 4;

	const int height = 14;
	DrawRectangle(bar_x, bar_y, unit_size.x, height, BLACK);

	float hp_portion_old = (float)renderer_unit.hp_shown_old / unit.character.get().max_hp;
	float hp_portion_current = (float)renderer_unit.hp_shown_current / unit.character.get().max_hp;

	// Update hp shown
	const float speed_old = 8;
	const float speed_current = 12;
	if (renderer_unit.hp_shown_old > unit.get_hp()) {
		renderer_unit.hp_shown_old -= speed_old * dt;
	}
	renderer_unit.hp_shown_current += (unit.get_hp() - renderer_unit.hp_shown_current) * dt * speed_current;

	DrawRectangle(bar_x + padding, bar_y + padding, (unit_size.x - 2*padding) * hp_portion_old, height - 2 * padding, ORANGE);
	DrawRectangle(bar_x + padding, bar_y + padding, (unit_size.x - 2*padding) * hp_portion_current, height - 2 * padding, RED);
}

void Combat_Renderer::on_battle_begin()
{
	SG_DEBUG("Combat renderer - battle begins");
	m_background = m_combat.get_background();
	m_units.clear();

	for (int i = 0; i < m_combat.get_hero_count(); i++) {
		const Combat_Unit& unit = m_combat.get_hero(i);
		m_units.insert(unit.get_id(), Combat_Renderer_Unit{
			.hp_shown_old = (float)unit.get_hp(),
			.hp_shown_current = (float)unit.get_hp(),
			.placement = get_hero_unit_placement(i)
		});
	}

	for (int i = 0; i < m_combat.get_enemy_count(); i++) {
		const Combat_Unit& unit = m_combat.get_enemy(i);
		m_units.insert(unit.get_id(), Combat_Renderer_Unit{
			.hp_shown_old = (float)unit.get_hp(),
			.hp_shown_current = (float)unit.get_hp(),
			.placement = get_enemy_unit_placement(i)
		});
	}
}

Battle_Unit_Placement Combat_Renderer::get_enemy_unit_placement(int index)
{
	const Array<Battle_Unit_Placement>& placements = m_combat.get_units_layout().enemies;
	if (m_combat.get_enemy_count() > placements.size()) {
		// FIXME - Possibly log an error without spamming the console
		index = placements.size() - 1;
	}

	return placements[index];
}

Battle_Unit_Placement Combat_Renderer::get_hero_unit_placement(int index)
{
	const Array<Battle_Unit_Placement>& placements = m_combat.get_units_layout().heroes;
	if (m_combat.get_hero_count() > placements.size()) {
		// FIXME - Possibly log an error without spamming the console
		index = placements.size() - 1;
	}

	return placements[index];
}

void Combat_Renderer::update_unit_position(int index, Combat_Renderer_Unit& unit, bool enemy, float dt)
{
	Battle_Unit_Placement placement = enemy ? get_enemy_unit_placement(index) : get_hero_unit_placement(index);
	const float speed = 5;

	unit.placement.position_x = unit.placement.position_x.lerp(placement.position_x, speed * dt);
	unit.placement.position_y = unit.placement.position_y.lerp(placement.position_y, speed * dt);
}

void Combat_Renderer::on_unit_hp_change(int id, int amount)
{
	Combat_Renderer_Unit* unit = m_units.get(id);
	assert(unit);
	
	if (amount < 0)
		unit->time_since_damage_taken = 0;
	else
		unit->time_since_heal = 0;
}
