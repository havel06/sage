#include "combat_controller.hpp"
#include "ability.hpp"
#include "character_profile.hpp"
#include "combat.hpp"
#include "graphics/inventory_renderer.hpp"
#include "graphics/ui/box.hpp"
#include "graphics/ui/button.hpp"
#include "graphics/ui/text.hpp"
#include "graphics/ui/widget.hpp"
#include "graphics/ui/widget_visitor.hpp"
#include "io/gui_loader.hpp"
#include "utils/direction.hpp"
#include "utils/log.hpp"
#include "item/item.hpp"
#include <raylib/raylib.h>

Combat_Controller::Combat_Controller(Combat& combat, Inventory_Renderer& inv_rend) :
	m_combat{combat},
	m_inventory_renderer{inv_rend}
{
	m_combat.add_observer(*this);
	m_inventory_renderer.add_observer(*this);
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
		UI::Widget_Ptr fight_widget = m_option_widget->clone();
		UI::Widget_Ptr inventory_widget = m_option_widget->clone();

		UI::Widget* options_box = (m_action_menu_widget->get_widget_by_name("Options"));

		UI::Widget* fight_widget_name = fight_widget->get_widget_by_name("Name");
		UI::Widget* fight_widget_button = fight_widget->get_widget_by_name("Button");
		if (fight_widget_name && fight_widget_button) {
			UI::Text_Widget_Visitor name_visitor{[&](UI::Text& text){
				text.text = "Fight";
			}};

			UI::Button_Widget_Visitor button_visitor{[&](UI::Button& button){
				button.on_click = [this](){
					m_menu_state = Combat_Controller_Menu_State::selecting_ability;
				};
			}};

			fight_widget_name->accept_visitor(name_visitor);
			fight_widget_button->accept_visitor(button_visitor);
		}

		UI::Widget* inventory_widget_name = inventory_widget->get_widget_by_name("Name");
		UI::Widget* inventory_widget_button = inventory_widget->get_widget_by_name("Button");
		if (inventory_widget_name && inventory_widget_button) {
			UI::Text_Widget_Visitor name_visitor{[&](UI::Text& text){
				text.text = "Inventory";
			}};

			UI::Button_Widget_Visitor button_visitor{[&](UI::Button& button){
				button.on_click = [this](){
					m_menu_state = Combat_Controller_Menu_State::inventory;
				};
			}};

			inventory_widget_name->accept_visitor(name_visitor);
			inventory_widget_button->accept_visitor(button_visitor);
		}

		options_box->add_child((UI::Widget_Ptr&&)fight_widget);
		options_box->add_child((UI::Widget_Ptr&&)inventory_widget);

		m_action_menu_widget->focus_first();
	}
}

void Combat_Controller::on_hero_ability_selecting_begin()
{
	update_menus();
	m_menu_state = Combat_Controller_Menu_State::selecting_action;
}

void Combat_Controller::on_item_activate(Item& item)
{
	if (!m_combat.is_active()) {
		return;
	}

	if (item.assigned_sequence.has_value()) {
		m_combat.select_item(item);
		m_menu_state = Combat_Controller_Menu_State::selecting_action;
	}
}

void Combat_Controller::update_menus()
{
	const Character_Profile& hero = m_combat.get_unit_on_turn().character.get();

	UI::Widget* action_menu_title = m_action_menu_widget->get_widget_by_name("Title");
	UI::Widget* ability_menu_title = m_ability_menu_widget->get_widget_by_name("Title");
	if (action_menu_title && ability_menu_title) {
		UI::Text_Widget_Visitor visitor{[&](UI::Text& text){
			text.text = hero.name;
		}};
		action_menu_title->accept_visitor(visitor);
		ability_menu_title->accept_visitor(visitor);
	}

	UI::Widget* options_box = (m_ability_menu_widget->get_widget_by_name("Options"));
	if (options_box) {
		options_box->clear_children();

		for (int i = 0; i < hero.abilities.size(); i++) {
			const Ability& ability = hero.abilities[i];
			UI::Widget_Ptr option_widget = m_option_widget->clone();

			UI::Widget* name_widget = option_widget->get_widget_by_name("Name");
			UI::Widget* button_widget = option_widget->get_widget_by_name("Button");

			if (name_widget && button_widget) {
				UI::Text_Widget_Visitor name_visitor{[&](UI::Text& text){
					text.text = ability.name;
				}};

				UI::Button_Widget_Visitor button_visitor{[&](UI::Button& button){
					button.on_click = [this, i](){
						m_combat.select_ability(i);
					};
				}};

				name_widget->accept_visitor(name_visitor);
				button_widget->accept_visitor(button_visitor);
			}

			options_box->add_child((UI::Widget_Ptr&&)option_widget);
		}

		options_box->focus_first();
	}

	SG_DEBUG("Updated combat GUI");
}

void Combat_Controller::input_direction(Direction direction)
{
	switch (m_combat.get_state()) {
		case Combat_State::hero_selecting_ability:
			if (m_menu_state == Combat_Controller_Menu_State::selecting_action) {
				m_action_menu_widget->move_focus(direction);
			} else if (m_menu_state == Combat_Controller_Menu_State::inventory) {
				m_inventory_renderer.input_direction(direction);
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
			} else if (m_menu_state == Combat_Controller_Menu_State::inventory) {
				m_inventory_renderer.input_click();
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

void Combat_Controller::draw(float time_delta)
{
	if (!m_action_menu_widget || !m_ability_menu_widget || !m_option_widget)
		return;

	switch (m_combat.get_state()) {
		case Combat_State::hero_selecting_ability:
			if (m_menu_state == Combat_Controller_Menu_State::inventory) {
				m_inventory_renderer.show(true);
				return;
			} else {
				m_inventory_renderer.show(false);
			}

			if (m_menu_state == Combat_Controller_Menu_State::selecting_action) {
				m_action_menu_widget->draw_as_root(time_delta);
			} else {
				m_ability_menu_widget->draw_as_root(time_delta);
			}
			break;
		case Combat_State::hero_selecting_target:
			draw_selected_enemy(time_delta);
			break;
		default:
			return;
	}
}

void Combat_Controller::draw_selected_enemy(float dt)
{
	const Character_Profile& enemy = m_combat.get_enemy(m_selected_enemy).character.get();

	UI::Widget* title_widget = m_ability_menu_widget->get_widget_by_name("Title");
	UI::Widget* options_widget = m_ability_menu_widget->get_widget_by_name("Options");

	if (title_widget && options_widget) {
		UI::Text_Widget_Visitor visitor{[&](UI::Text& text){
			text.text = enemy.name;
		}};
		title_widget->accept_visitor(visitor);
		options_widget->clear_children();
	}

	m_ability_menu_widget->draw_as_root(dt);
}
