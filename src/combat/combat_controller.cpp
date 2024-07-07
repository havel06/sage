#include "combat_controller.hpp"
#include "ability.hpp"
#include "character_profile.hpp"
#include "combat.hpp"
#include "graphics/ui/box.hpp"
#include "graphics/ui/button.hpp"
#include "graphics/ui/text.hpp"
#include "graphics/ui/widget.hpp"
#include "io/gui_loader.hpp"
#include "utils/direction.hpp"
#include "utils/log.hpp"
#include <raylib/raylib.h>

Combat_Controller::Combat_Controller(Combat& combat) :
	m_combat{combat}
{
	m_combat.add_observer(*this);
}

void Combat_Controller::load(GUI_Loader& loader, const String& menu_filename, const String& option_filename)
{
	if (menu_filename.empty() || option_filename.empty())
		return;

	m_menu_widget = loader.load(menu_filename);
	m_option_widget = loader.load(option_filename);
}

void Combat_Controller::on_hero_turn_begin()
{
	update_ability_menu();
}

void Combat_Controller::update_ability_menu()
{
	// FIXME - check that widgets got by name exist
	const Character_Profile& hero = m_combat.get_unit_on_turn().character;

	// FIXME - safe cast
	((UI::Text*)(m_menu_widget->get_widget_by_name("Title")))->text = hero.name;

	UI::Widget* options_box = (m_menu_widget->get_widget_by_name("Options"));
	options_box->clear_children();

	for (int i = 0; i < hero.abilities.size(); i++) {
		const Ability& ability = hero.abilities[i];
		UI::Widget_Ptr option_widget = m_option_widget->clone();

		// FIXME - safe cast
		((UI::Text*)(option_widget->get_widget_by_name("Name")))->text = ability.name;
		((UI::Button*)(option_widget->get_widget_by_name("Button")))->on_click = [this, i](){
			m_selected_ability = i;
		};

		options_box->add_child((UI::Widget_Ptr&&)option_widget);
	}

	options_box->focus_first();

	SG_DEBUG("Updated combat GUI");
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
	if (!m_menu_widget || !m_option_widget)
		return;

	if (m_combat.is_hero_turn()) {
		if (m_state == Combat_Controller_State::selecting_ability) {
			m_menu_widget->draw_as_root(0); // FIXME - time delta
		} else {
			draw_selected_enemy();
		}
	}
}

void Combat_Controller::draw_selected_enemy()
{
	const Character_Profile& enemy = m_combat.get_enemy(m_selected_enemy).character;

	// FIXME - safe cast
	((UI::Text*)(m_menu_widget->get_widget_by_name("Title")))->text = enemy.name;
	(m_menu_widget->get_widget_by_name("Options"))->clear_children();

	m_menu_widget->draw_as_root(0); // FIXME - time delta
}
