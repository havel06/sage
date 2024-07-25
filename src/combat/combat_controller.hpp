#pragma once
#include "utils/string.hpp"
#include "graphics/ui/widget.hpp"
#include "combat.hpp"

// fwd
class GUI_Loader;
class Inventory_Renderer;

enum class Combat_Controller_Menu_State
{
	selecting_action,
	selecting_ability,
	selecting_enemy,
	inventory,
};

// FIXME - move some rendering (future effects and such) into cobmat_renderer

class Combat_Controller : public Combat_Observer
{
public:
	Combat_Controller(Combat&, Inventory_Renderer&);
	~Combat_Controller();
	void load(GUI_Loader&, const String& menu_filename, const String& option_filename);
	void input_direction(Direction);
	void input_enter();
	void draw(float time_delta);
private:
	void on_hero_ability_selecting_begin() override;
	void update_menus();

	void draw_selected_enemy();

	int m_selected_enemy = 0;
	Combat_Controller_Menu_State m_menu_state = Combat_Controller_Menu_State::selecting_action;
	Combat& m_combat;
	Inventory_Renderer& m_inventory_renderer;

	UI::Widget_Ptr m_action_menu_widget;
	UI::Widget_Ptr m_ability_menu_widget;
	UI::Widget_Ptr m_option_widget;
};
