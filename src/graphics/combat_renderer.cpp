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
	draw_party(dt);
	draw_enemies(dt);

	ClearBackground(SKYBLUE);
	DrawText("combat!", 100, 100, 50, WHITE);
}

void Combat_Renderer::draw_party(float dt)
{
	int x = GetScreenWidth() / 5;
	int y = GetScreenHeight() / 6;

	const int size = GetScreenHeight() / 8;
	const int margin = size / 3;

	for (int i = 0; i < m_party.get_character_count(); i++) {
		Rectf transform = {
			.position = Vec2f{(float)x, (float)y},
			.size = Vec2f{(float)size, (float)size}
		};

		const Combat_Unit& unit = m_combat.get_hero(i);

		unit.character.get().sprite_right.draw(transform, dt);
		draw_hp_bar({x, y}, size, unit, m_heroes[i], dt);

		y += size + margin;
	}
}

void Combat_Renderer::draw_enemies(float dt)
{
	const int size = GetScreenHeight() / 8;
	const int margin = size / 3;

	int x = GetScreenWidth() / 5 * 4 - size;
	int y = GetScreenHeight() / 6;

	for (int i = 0; i < m_combat.get_enemy_count(); i++) {
		Rectf transform = {
			.position = Vec2f{(float)x, (float)y},
			.size = Vec2f{(float)size, (float)size}
		};

		const Combat_Unit& unit = m_combat.get_enemy(i);

		unit.character.get().sprite_left.draw(transform, dt);
		draw_hp_bar({x, y}, size, unit, m_enemies[i], dt);

		y += size + margin;
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
	m_heroes.clear();
	m_enemies.clear();

	for (int i = 0; i < m_combat.get_hero_count(); i++) {
		const Combat_Unit& unit = m_combat.get_hero(i);
		m_heroes.push_back(Combat_Renderer_Unit{
			.hp_shown_old = (float)unit.get_hp(),
			.hp_shown_current = (float)unit.get_hp()
		});
	}

	for (int i = 0; i < m_combat.get_enemy_count(); i++) {
		const Combat_Unit& unit = m_combat.get_enemy(i);
		m_enemies.push_back(Combat_Renderer_Unit{
			.hp_shown_old = (float)unit.get_hp(),
			.hp_shown_current = (float)unit.get_hp(),
		});
	}
}
