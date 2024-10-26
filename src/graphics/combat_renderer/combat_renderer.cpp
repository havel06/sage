#include "combat_renderer.hpp"
#include "combat/battle_desc.hpp"
#include "combat/combat_controller.hpp"
#include "combat/combat_unit.hpp"
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
}

void Combat_Renderer::draw_background(float dt)
{
	const Animated_Sprite& background = m_combat.get_battle().get_background();

	// Render sprite to cover screen
	const float texture_size_x = background.get_current_frame().texture_clip.size.x;
	const float texture_size_y = background.get_current_frame().texture_clip.size.y;

	const float scale_x = GetScreenWidth() / texture_size_x;
	const float scale_y = GetScreenHeight() / texture_size_y;

	if (scale_x > scale_y) {
		// Sprite needs to stretch horizontally
		background.draw({{0, 0}, {texture_size_x * scale_x, texture_size_y * scale_x}}, dt);
	} else {
		// Sprite needs to stretch vertically
		background.draw({{0, 0}, {texture_size_x * scale_y, texture_size_y * scale_y}}, dt);
	}
}

void Combat_Renderer::draw_party(float dt)
{
	for (int i = 0; i < m_combat.get_battle().get_hero_count(); i++) {
		const Combat_Unit& combat_unit = m_combat.get_battle().get_hero(i);
		const bool selected = m_combat_controller.is_selecting_hero() &&
				m_combat_controller.get_current_selected_target() == i;

		draw_unit(combat_unit, i, selected, dt);
	}
}

void Combat_Renderer::draw_enemies(float dt)
{
	for (int i = 0; i < m_combat.get_battle().get_enemy_count(); i++) {
		const Combat_Unit& combat_unit = m_combat.get_battle().get_enemy(i);
		const bool selected = m_combat_controller.is_selecting_enemy() &&
				m_combat_controller.get_current_selected_target() == i;

		draw_unit(combat_unit, i, selected, dt);
	}
}

void Combat_Renderer::draw_unit(const Combat_Unit& combat_unit, int index, bool selected, float dt)
{
	Combat_Renderer_Unit* renderer_unit = m_units.get(combat_unit.get_id());
	assert(renderer_unit);
	update_unit_position(index, *renderer_unit, combat_unit.get_side(), dt);
	renderer_unit->draw(combat_unit, selected, dt);
}

void Combat_Renderer::on_battle_begin()
{
	SG_DEBUG("Combat renderer - battle begins");
	m_units.clear();

	for (int i = 0; i < m_combat.get_battle().get_hero_count(); i++) {
		const Combat_Unit& unit = m_combat.get_battle().get_hero(i);
		m_units.insert(unit.get_id(), Combat_Renderer_Unit{
			m_shader,
			(float)unit.get_hp(),
			get_hero_unit_placement(i)
		});
	}

	for (int i = 0; i < m_combat.get_battle().get_enemy_count(); i++) {
		const Combat_Unit& unit = m_combat.get_battle().get_enemy(i);
		m_units.insert(unit.get_id(), Combat_Renderer_Unit{
			m_shader,
			(float)unit.get_hp(),
			get_enemy_unit_placement(i)
		});
	}
}

Battle_Unit_Placement Combat_Renderer::get_enemy_unit_placement(int index)
{
	const Array<Battle_Unit_Placement>& placements = m_combat.get_battle().get_units_layout().enemies;
	if (m_combat.get_battle().get_enemy_count() > placements.size()) {
		// FIXME - Possibly log an error without spamming the console
		index = placements.size() - 1;
	}

	return placements[index];
}

Battle_Unit_Placement Combat_Renderer::get_hero_unit_placement(int index)
{
	const Array<Battle_Unit_Placement>& placements = m_combat.get_battle().get_units_layout().heroes;
	if (m_combat.get_battle().get_hero_count() > placements.size()) {
		// FIXME - Possibly log an error without spamming the console
		index = placements.size() - 1;
	}

	return placements[index];
}

void Combat_Renderer::update_unit_position(int index, Combat_Renderer_Unit& unit, Combat_Unit_Side side, float dt)
{
	Battle_Unit_Placement placement = side == Combat_Unit_Side::enemy ? get_enemy_unit_placement(index) : get_hero_unit_placement(index);
	const float speed = 5;

	unit.placement.position_x = unit.placement.position_x.lerp(placement.position_x, speed * dt);
	unit.placement.position_y = unit.placement.position_y.lerp(placement.position_y, speed * dt);
}

void Combat_Renderer::on_unit_hp_change(int id, int amount)
{
	Combat_Renderer_Unit* unit = m_units.get(id);
	assert(unit);
	
	if (amount < 0)
		unit->begin_effect_damage_taken();
	else
		unit->begin_effect_heal();
}
