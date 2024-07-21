#include "combat_renderer.hpp"
#include "party.hpp"
#include "utils/rect.hpp"
#include "combat/combat.hpp"
#include <raylib/raylib.h>

Combat_Renderer::Combat_Renderer(const Party& party, const Combat& combat) :
	m_party{party},
	m_combat{combat}
{
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
		draw_hp_bar({x, y}, size, unit);

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

		unit.character.get().sprite_right.draw(transform, dt);
		draw_hp_bar({x, y}, size, unit);

		y += size + margin;
	}
}

void Combat_Renderer::draw_hp_bar(const Vec2i unit_pos, const int unit_size, const Combat_Unit& unit)
{
	const int bar_x = unit_pos.x;
	const int bar_y = unit_pos.y + unit_size + 8;
	const int padding = 4;

	const int height = 14;
	DrawRectangle(bar_x, bar_y, unit_size, height, BLACK);

	float hp_portion = (float)unit.hp / unit.character.get().max_hp;

	DrawRectangle(bar_x + padding, bar_y + padding, (unit_size - 2*padding) * hp_portion, height - 2 * padding, RED);

	(void)padding;
	(void)unit;
}
