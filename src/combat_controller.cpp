#include "combat_controller.hpp"
#include "character_profile.hpp"
#include "combat.hpp"
#include "io/gui_loader.hpp"
#include "utils/direction.hpp"
#include <raylib/raylib.h>

Combat_Controller::Combat_Controller(Combat& combat) :
	m_combat{combat}
{
}

void Combat_Controller::load(GUI_Loader& loader, const String& project_root)
{
	String path = project_root;
	path.append("/combat_menu.json");
	m_menu_widget = loader.load(path.data());

	m_menu_widget->focus_first();
}

void Combat_Controller::input_direction(Direction direction)
{
	if (!m_combat.is_hero_turn())
		return;

	if (m_state == Combat_Controller_State::selecting_ability) {
		m_menu_widget->move_focus(direction);
	}
}

void Combat_Controller::enter()
{
	if (!m_combat.is_hero_turn())
		return;

	if (m_state == Combat_Controller_State::selecting_ability) {
		m_menu_widget->process_click();
		m_state = Combat_Controller_State::selecting_enemy;
	} else {
		m_combat.use_ability(m_selected_ability, m_selected_enemy);
		m_state = Combat_Controller_State::selecting_ability;
	}
}

void Combat_Controller::draw()
{
	if (m_combat.is_hero_turn()) {
		if (m_state == Combat_Controller_State::selecting_ability) {
			// FIXME - draw abilities
		} else {
			// FIXME - draw selected enemy
		}
	}

	m_menu_widget->draw_as_root(0); // FIXME - time delta
}

void Combat_Controller::draw_abilities()
{
	// FIXME
	const Character_Profile& character = m_combat.get_unit_on_turn().character;

	for (int i = 0; i < character.abilities.size(); i++) {
		//DrawText(character.abilities[i].name.data(), x, y, 20, colour);
	}
}

void Combat_Controller::draw_selected_enemy()
{
	// FIXME
	//DrawText(m_combat.get_enemy(m_selected_enemy).character.name.data(), x, y, 30, WHITE);
}
