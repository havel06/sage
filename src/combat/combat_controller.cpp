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

Combat_Controller::~Combat_Controller()
{
	m_combat.remove_observer(*this);
}

void Combat_Controller::load(GUI_Loader& loader, const String& menu_filename, const String& option_filename)
{
	if (menu_filename.empty() || option_filename.empty())
		return;

	m_action_menu_widget = loader.load(menu_filename);
	m_option_widget = loader.load(option_filename);

	if (m_action_menu_widget && m_option_widget) {
		m_ability_menu_widget = m_action_menu_widget->clone();

		// Set up action menu
		// FIXME - safe cast
		UI::Widget* options_box = (m_action_menu_widget->get_widget_by_name("Options"));
		
		UI::Widget_Ptr fight_widget = m_option_widget->clone();
		UI::Widget_Ptr inventory_widget = m_option_widget->clone();

		// FIXME - safe cast
		((UI::Text*)(fight_widget->get_widget_by_name("Name")))->text = "Fight";
		((UI::Button*)(fight_widget->get_widget_by_name("Button")))->on_click = [this](){
			m_menu_state = Combat_Controller_Menu_State::selecting_ability;
		};
		((UI::Text*)(inventory_widget->get_widget_by_name("Name")))->text = "Inventory";
		((UI::Button*)(inventory_widget->get_widget_by_name("Button")))->on_click = [](){
			SG_DEBUG("TODO - inventory");
		};

		options_box->add_child((UI::Widget_Ptr&&)fight_widget);
		options_box->add_child((UI::Widget_Ptr&&)inventory_widget);

		m_action_menu_widget->focus_first();
	}
}

void Combat_Controller::on_hero_turn_begin()
{
	update_menus();
	m_menu_state = Combat_Controller_Menu_State::selecting_action;
}

void Combat_Controller::update_menus()
{
	// FIXME - check that widgets got by name exist

	const Character_Profile& hero = m_combat.get_unit_on_turn().character.get();

	// FIXME - safe cast
	((UI::Text*)(m_action_menu_widget->get_widget_by_name("Title")))->text = hero.name;
	((UI::Text*)(m_ability_menu_widget->get_widget_by_name("Title")))->text = hero.name;

	UI::Widget* options_box = (m_ability_menu_widget->get_widget_by_name("Options"));
	options_box->clear_children();

	for (int i = 0; i < hero.abilities.size(); i++) {
		const Ability& ability = hero.abilities[i];
		UI::Widget_Ptr option_widget = m_option_widget->clone();

		// FIXME - safe cast
		((UI::Text*)(option_widget->get_widget_by_name("Name")))->text = ability.name;
		((UI::Button*)(option_widget->get_widget_by_name("Button")))->on_click = [this, i](){
			m_combat.select_ability(i);
		};

		options_box->add_child((UI::Widget_Ptr&&)option_widget);
	}

	options_box->focus_first();

	SG_DEBUG("Updated combat GUI");
}

void Combat_Controller::input_direction(Direction direction)
{
	switch (m_combat.get_state()) {
		case Combat_State::hero_selecting_ability:
			if (m_menu_state == Combat_Controller_Menu_State::selecting_action) {
				m_action_menu_widget->move_focus(direction);
			} else {
				m_ability_menu_widget->move_focus(direction);
			}
			break;
		case Combat_State::hero_selecting_target:
			// FIXME - enemy selection
			break;
		default:
			return;
	}
}

void Combat_Controller::input_enter()
{
	switch (m_combat.get_state()) {
		case Combat_State::hero_selecting_ability:
			if (m_menu_state == Combat_Controller_Menu_State::selecting_action) {
				m_action_menu_widget->process_click();
			} else {
				m_ability_menu_widget->process_click();
			}
			break;
		case Combat_State::hero_selecting_target:
			m_combat.select_target(m_selected_enemy);
			break;
		default:
			return;
	}
}

void Combat_Controller::draw()
{
	if (!m_action_menu_widget || !m_ability_menu_widget || !m_option_widget)
		return;

	switch (m_combat.get_state()) {
		case Combat_State::hero_selecting_ability:
			if (m_menu_state == Combat_Controller_Menu_State::selecting_action) {
				m_action_menu_widget->draw_as_root(0); // FIXME - time delta
			} else {
				m_ability_menu_widget->draw_as_root(0); // FIXME - time delta
			}
			break;
		case Combat_State::hero_selecting_target:
			draw_selected_enemy();
			break;
		default:
			return;
	}
}

void Combat_Controller::draw_selected_enemy()
{
	const Character_Profile& enemy = m_combat.get_enemy(m_selected_enemy).character.get();

	// FIXME - safe cast
	((UI::Text*)(m_ability_menu_widget->get_widget_by_name("Title")))->text = enemy.name;
	(m_ability_menu_widget->get_widget_by_name("Options"))->clear_children();

	m_ability_menu_widget->draw_as_root(0); // FIXME - time delta
}
