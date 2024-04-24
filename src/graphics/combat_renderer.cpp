#include "combat_renderer.hpp"
#include "party.hpp"
#include "utils/rect.hpp"
#include <raylib/raylib.h>

Combat_Renderer::Combat_Renderer(const Party& party) :
	m_party{party}
{

}

void Combat_Renderer::draw()
{
	draw_party();

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
