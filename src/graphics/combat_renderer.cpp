#include "combat_renderer.hpp"
#include "party.hpp"
#include "utils/rect.hpp"
#include "combat.hpp"
#include <raylib/raylib.h>

Combat_Renderer::Combat_Renderer(const Party& party, const Combat& combat) :
	m_party{party},
	m_combat{combat}
{
}

void Combat_Renderer::draw()
{
	draw_party();
	draw_enemies();

	ClearBackground(SKYBLUE);
	DrawText("combat!", 100, 100, 50, WHITE);
}

void Combat_Renderer::draw_party()
{
	int x = GetScreenWidth() / 5;
	int y = GetScreenHeight() / 6;

	const int size = GetScreenHeight() / 8;
	const int margin = size / 4;

	for (int i = 0; i < m_party.get_character_count(); i++) {
		Rectf transform = {
			.position = Vec2f{(float)x, (float)y},
			.size = Vec2f{(float)size, (float)size}
		};
		m_party.get_character(i).sprite_right.draw(transform);
		y += size + margin;
	}
}

void Combat_Renderer::draw_enemies()
{
	const int size = GetScreenHeight() / 8;
	const int margin = size / 4;

	int x = GetScreenWidth() / 5 * 4 - size;
	int y = GetScreenHeight() / 6;

	for (int i = 0; i < m_combat.get_enemy_count(); i++) {
		Rectf transform = {
			.position = Vec2f{(float)x, (float)y},
			.size = Vec2f{(float)size, (float)size}
		};
		m_combat.get_enemy(i).sprite_left.draw(transform);
		y += size + margin;
	}
}
