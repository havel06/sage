#include "combat_renderer.hpp"
#include "party.hpp"
#include "utils/log.hpp"
#include "utils/rect.hpp"
#include "combat/combat.hpp"
#include <raylib/raylib.h>

Combat_Renderer::Combat_Renderer(const Party& party, Combat& combat) :
	m_party{party},
	m_combat{combat}
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
	const int size = GetScreenWidth() / 13;

	for (int i = 0; i < m_party.get_character_count(); i++) {
		const Combat_Unit& unit = m_combat.get_hero(i);
		Vec2i screen_size = {GetScreenWidth(), GetScreenHeight()};
		const int pos_x = m_heroes[i].pos_x.to_pixels(screen_size);
		const int pos_y = m_heroes[i].pos_y.to_pixels(screen_size);

		Rectf transform = {
			.position = Vec2f{(float)pos_x, (float)pos_y},
			.size = Vec2f{(float)size, (float)size}
		};

		unit.character.get().sprite_right.draw(transform, dt);

		draw_hp_bar({pos_x, pos_y}, size, unit, m_heroes[i], dt);
	}
}

void Combat_Renderer::draw_enemies(float dt)
{
	const int size = GetScreenWidth() / 13;

	for (int i = 0; i < m_combat.get_enemy_count(); i++) {
		const Combat_Unit& unit = m_combat.get_enemy(i);
		Vec2i screen_size = {GetScreenWidth(), GetScreenHeight()};
		const int pos_x = m_enemies[i].pos_x.to_pixels(screen_size);
		const int pos_y = m_enemies[i].pos_y.to_pixels(screen_size);

		Rectf transform = {
			.position = Vec2f{(float)pos_x, (float)pos_y},
			.size = Vec2f{(float)size, (float)size}
		};

		unit.character.get().sprite_left.draw(transform, dt);

		draw_hp_bar({pos_x, pos_y}, size, unit, m_enemies[i], dt);
	}
}

void Combat_Renderer::draw_hp_bar(const Vec2i unit_pos, const int unit_size, const Combat_Unit& unit, Combat_Renderer_Unit& renderer_unit, float dt)
{
	const int bar_x = unit_pos.x;
	const int bar_y = unit_pos.y + unit_size + 8;
	const int padding = 4;

	const int height = 14;
	DrawRectangle(bar_x, bar_y, unit_size, height, BLACK);

	float hp_portion_old = (float)renderer_unit.hp_shown_old / unit.character.get().max_hp;
	float hp_portion_current = (float)renderer_unit.hp_shown_current / unit.character.get().max_hp;

	// Update hp shown
	const float speed_old = 8;
	const float speed_current = 12;
	if (renderer_unit.hp_shown_old > unit.get_hp()) {
		renderer_unit.hp_shown_old -= speed_old * dt;
	}
	renderer_unit.hp_shown_current += (unit.get_hp() - renderer_unit.hp_shown_current) * dt * speed_current;

	DrawRectangle(bar_x + padding, bar_y + padding, (unit_size - 2*padding) * hp_portion_old, height - 2 * padding, ORANGE);
	DrawRectangle(bar_x + padding, bar_y + padding, (unit_size - 2*padding) * hp_portion_current, height - 2 * padding, RED);

	(void)padding;
	(void)unit;
}

void Combat_Renderer::on_battle_begin()
{
	SG_DEBUG("Combat renderer - battle begins");
	m_background = m_combat.get_background();
	m_heroes.clear();
	m_enemies.clear();

	for (int i = 0; i < m_combat.get_hero_count(); i++) {
		const Combat_Unit& unit = m_combat.get_hero(i);
		m_heroes.push_back(Combat_Renderer_Unit{
			.hp_shown_old = (float)unit.get_hp(),
			.hp_shown_current = (float)unit.get_hp(),
			.pos_x = { .parent_width = 0.2 },
			.pos_y = get_hero_position_y(i)
		});
	}

	for (int i = 0; i < m_combat.get_enemy_count(); i++) {
		const Combat_Unit& unit = m_combat.get_enemy(i);
		m_enemies.push_back(Combat_Renderer_Unit{
			.hp_shown_old = (float)unit.get_hp(),
			.hp_shown_current = (float)unit.get_hp(),
			.pos_x = { .parent_width = 0.675 },
			.pos_y = get_enemy_position_y(i)
		});
	}
}

UI::Size Combat_Renderer::get_hero_position_y(int index)
{
	return { .parent_height = 0.15f + index * 0.05f };
}

UI::Size Combat_Renderer::get_enemy_position_y(int index)
{
	return { .parent_height = 0.15f + index * 0.05f };
}
