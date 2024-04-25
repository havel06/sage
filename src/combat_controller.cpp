#include "combat_controller.hpp"
#include "character_profile.hpp"
#include "combat.hpp"
#include <raylib/raylib.h>

Combat_Controller::Combat_Controller(Combat& combat) :
	m_combat{combat}
{
}

void Combat_Controller::go_down()
{
	m_selected_ability++;
	fix_selected_ability_index();
}

void Combat_Controller::go_up()
{
	m_selected_ability--;
	fix_selected_ability_index();
}

void Combat_Controller::go_right()
{

}

void Combat_Controller::go_left()
{

}

void Combat_Controller::enter()
{

}

void Combat_Controller::draw()
{
	// Draw background
	const int width = GetScreenWidth() - 2 * m_margin;
	const int start_y =  GetScreenHeight() - m_height - m_margin;

	DrawRectangle(m_margin, start_y, width, m_height, {0, 0, 0, 200});

	if (m_combat.is_hero_turn()) {
		draw_abilities();
	}
}

void Combat_Controller::draw_abilities()
{
	const int padding = 15;
	const int x = m_margin + padding;
	int y = GetScreenHeight() - m_height - m_margin + padding;
	const Character_Profile& character = m_combat.get_character_on_turn();
	DrawText(character.name.data(), x, y, 25, WHITE);
	y += 40;

	for (int i = 0; i < character.abilities.size(); i++) {
		Color colour = m_selected_ability == i ? YELLOW : WHITE;
		DrawText(character.abilities[i].name.data(), x, y, 20, colour);
		y += 25;
	}
}

void Combat_Controller::fix_selected_ability_index()
{
	const Character_Profile& character = m_combat.get_character_on_turn();
	const int ability_count = character.abilities.size();

	if (m_selected_ability < 0) {
		m_selected_ability = ability_count - 1;
	} else if (m_selected_ability >= ability_count) {
		m_selected_ability = 0;
	}
}
