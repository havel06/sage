#include "combat_controller.hpp"
#include "ability.hpp"
#include "battle_turn.hpp"
#include "character_profile.hpp"
#include "combat.hpp"
#include "combat/combat_unit.hpp"
#include "graphics/inventory_renderer.hpp"
#include "graphics/game_ui/widgets/box.hpp"
#include "graphics/game_ui/widgets/button.hpp"
#include "graphics/game_ui/formatted_text.hpp"
#include "graphics/game_ui/widgets/text.hpp"
#include "graphics/game_ui/widget.hpp"
#include "graphics/game_ui/widget_visitor.hpp"
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
		Game_UI::Widget_Ptr fight_widget = m_option_widget->clone();
		Game_UI::Widget_Ptr inventory_widget = m_option_widget->clone();

		Game_UI::Widget* options_box = (m_action_menu_widget->get_widget_by_name("Options"));

		Game_UI::Widget* fight_widget_name = fight_widget->get_widget_by_name("Name");
		Game_UI::Widget* fight_widget_button = fight_widget->get_widget_by_name("Button");
		if (fight_widget_name && fight_widget_button) {
			Game_UI::Text_Widget_Visitor name_visitor{[&](Game_UI::Text& text){
				text.text = Game_UI::Formatted_Text{"Fight"};
			}};

			Game_UI::Button_Widget_Visitor button_visitor{[&](Game_UI::Button& button){
				button.on_click = [this](){
					m_menu_state = Combat_Controller_Menu_State::selecting_ability;
				};
			}};

			fight_widget_name->accept_visitor(name_visitor);
			fight_widget_button->accept_visitor(button_visitor);
		}

		Game_UI::Widget* inventory_widget_name = inventory_widget->get_widget_by_name("Name");
		Game_UI::Widget* inventory_widget_button = inventory_widget->get_widget_by_name("Button");
		if (inventory_widget_name && inventory_widget_button) {
			Game_UI::Text_Widget_Visitor name_visitor{[&](Game_UI::Text& text){
				text.text = Game_UI::Formatted_Text{"Inventory"};
			}};

			Game_UI::Button_Widget_Visitor button_visitor{[&](Game_UI::Button& button){
				button.on_click = [this](){
					if (!m_inventory_renderer.is_inventory_empty())
						m_menu_state = Combat_Controller_Menu_State::inventory;
				};
			}};

			inventory_widget_name->accept_visitor(name_visitor);
			inventory_widget_button->accept_visitor(button_visitor);
		}

		if (options_box) {
			options_box->add_child((Game_UI::Widget_Ptr&&)fight_widget);
			options_box->add_child((Game_UI::Widget_Ptr&&)inventory_widget);
		}

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
		m_combat.get_battle().get_current_turn().select_item(item);
		m_menu_state = Combat_Controller_Menu_State::selecting_action;
	}
}

void Combat_Controller::update_menus()
{
	const Character_Profile& hero = m_combat.get_battle().get_unit_on_turn().character.get();

	Game_UI::Widget* action_menu_title = m_action_menu_widget->get_widget_by_name("Title");
	Game_UI::Widget* ability_menu_title = m_ability_menu_widget->get_widget_by_name("Title");
	if (action_menu_title && ability_menu_title) {
		Game_UI::Text_Widget_Visitor visitor{[&](Game_UI::Text& text){
			text.text = hero.name;
		}};
		action_menu_title->accept_visitor(visitor);
		ability_menu_title->accept_visitor(visitor);
	}

	Game_UI::Widget* options_box = (m_ability_menu_widget->get_widget_by_name("Options"));
	if (options_box) {
		options_box->clear_children();

		for (int i = 0; i < hero.abilities.size(); i++) {
			const Ability& ability = hero.abilities[i];
			Game_UI::Widget_Ptr option_widget = m_option_widget->clone();

			Game_UI::Widget* name_widget = option_widget->get_widget_by_name("Name");
			Game_UI::Widget* button_widget = option_widget->get_widget_by_name("Button");

			if (name_widget && button_widget) {
				Game_UI::Text_Widget_Visitor name_visitor{[&](Game_UI::Text& text){
					text.text = ability.name;
				}};

				Game_UI::Button_Widget_Visitor button_visitor{[&](Game_UI::Button& button){
					button.on_click = [this, i](){
						m_combat.get_battle().get_current_turn().select_ability(i);
					};
				}};

				name_widget->accept_visitor(name_visitor);
				button_widget->accept_visitor(button_visitor);
			}

			options_box->add_child((Game_UI::Widget_Ptr&&)option_widget);
		}

		options_box->focus_first();
	}

	SG_DEBUG("Updated combat GUI");
}

void Combat_Controller::input_direction(Direction direction)
{
	if (m_combat.get_battle().get_current_side() != Combat_Unit_Side::hero)
		return;

	switch (m_combat.get_battle().get_current_turn().get_state()) {
		case Battle_Turn_State::selecting_action:
			if (m_menu_state == Combat_Controller_Menu_State::selecting_action) {
				m_action_menu_widget->move_focus(direction);
			} else if (m_menu_state == Combat_Controller_Menu_State::inventory) {
				m_inventory_renderer.input_direction(direction);
			} else {
				m_ability_menu_widget->move_focus(direction);
			}
			break;
		case Battle_Turn_State::selecting_enemy_target:
			switch (direction) {
				case Direction::up:
					m_selected_target--;
					if (m_selected_target < 0) {
						m_selected_target = m_combat.get_battle().get_enemy_count() - 1;
					}
					break;
				case Direction::down:
					m_selected_target++;
					m_selected_target = m_selected_target % m_combat.get_battle().get_enemy_count();
					break;
				default:
					break;
			}
			break;
		case Battle_Turn_State::selecting_ally_target:
			switch (direction) {
				case Direction::up:
					m_selected_target--;
					if (m_selected_target < 0) {
						m_selected_target = m_combat.get_battle().get_hero_count() - 1;
					}
					break;
				case Direction::down:
					m_selected_target++;
					m_selected_target = m_selected_target % m_combat.get_battle().get_hero_count();
					break;
				default:
					break;
			}
			break;
		default:
			return;
	}
}

void Combat_Controller::input_enter()
{
	if (m_combat.get_battle().get_current_side() != Combat_Unit_Side::hero)
		return;

	switch (m_combat.get_battle().get_current_turn().get_state()) {
		case Battle_Turn_State::selecting_action:
			if (m_menu_state == Combat_Controller_Menu_State::selecting_action) {
				m_action_menu_widget->process_click();
			} else if (m_menu_state == Combat_Controller_Menu_State::inventory) {
				m_inventory_renderer.input_click();
			} else {
				m_ability_menu_widget->process_click();
			}
			break;
		case Battle_Turn_State::selecting_enemy_target:
		case Battle_Turn_State::selecting_ally_target:
			m_combat.get_battle().get_current_turn().select_target(m_selected_target);
			m_selected_target = 0;
			break;
		default:
			return;
	}
}

void Combat_Controller::input_escape()
{
	if (m_combat.get_battle().get_current_side() != Combat_Unit_Side::hero)
		return;

	if (m_combat.get_battle().get_current_turn().get_state() != Battle_Turn_State::selecting_action)
		return;

	switch (m_menu_state) {
		case Combat_Controller_Menu_State::inventory:
		case Combat_Controller_Menu_State::selecting_ability:
			m_menu_state = Combat_Controller_Menu_State::selecting_action;
			break;
		default:
			break;
	}
}

void Combat_Controller::draw(float time_delta)
{
	if (!m_action_menu_widget || !m_ability_menu_widget || !m_option_widget)
		return;

	if (m_combat.get_battle().get_current_side() != Combat_Unit_Side::hero)
		return;

	switch (m_combat.get_battle().get_current_turn().get_state()) {
		case Battle_Turn_State::selecting_action:
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
		case Battle_Turn_State::selecting_enemy_target:
			draw_selected_target(time_delta, true);
			break;
		case Battle_Turn_State::selecting_ally_target:
			draw_selected_target(time_delta, false);
			break;
		default:
			return;
	}
}

void Combat_Controller::draw_selected_target(float dt, bool is_enemy)
{
	const Character_Profile& target = is_enemy ?
		m_combat.get_battle().get_enemy(m_selected_target).character.get() :
		m_combat.get_battle().get_hero(m_selected_target).character.get();

	Game_UI::Widget* title_widget = m_ability_menu_widget->get_widget_by_name("Title");
	Game_UI::Widget* options_widget = m_ability_menu_widget->get_widget_by_name("Options");

	if (title_widget && options_widget) {
		Game_UI::Text_Widget_Visitor visitor{[&](Game_UI::Text& text){
			text.text = target.name;
		}};
		title_widget->accept_visitor(visitor);
		options_widget->clear_children();
	}

	m_ability_menu_widget->draw_as_root(dt);
}

bool Combat_Controller::is_selecting_enemy() const
{
	if (m_combat.get_battle().get_current_side() != Combat_Unit_Side::hero)
		return false;

	return m_combat.get_battle().get_current_turn().get_state() == Battle_Turn_State::selecting_enemy_target;
}

bool Combat_Controller::is_selecting_hero() const
{
	if (m_combat.get_battle().get_current_side() != Combat_Unit_Side::hero)
		return false;
	return m_combat.get_battle().get_current_turn().get_state() == Battle_Turn_State::selecting_ally_target;
}
