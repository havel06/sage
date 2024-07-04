#pragma once
#include "utils/string.hpp"
#include "graphics/ui/widget.hpp"
#include "combat.hpp"

// fwd
class GUI_Loader;

enum class Combat_Controller_State
{
	selecting_ability,
	selecting_enemy,
};

// FIXME - move some rendering (future effects and such) into cobmat_renderer

class Combat_Controller : public Combat_Observer
{
public:
	Combat_Controller(Combat&);
	void load(GUI_Loader&, const String& menu_filename, const String& option_filename);
	void input_direction(Direction);
	void enter();
	void draw();
private:
	void on_hero_turn_begin() override;
	void update_ability_menu();

	void draw_abilities(); // FIXME - remove
	void draw_selected_enemy();

	int m_selected_ability = 0; // Set by buttons in GUI
	int m_selected_enemy = 0;
	Combat_Controller_State m_state = Combat_Controller_State::selecting_ability;
	Combat& m_combat;

	UI::Widget_Ptr m_menu_widget;
	UI::Widget_Ptr m_option_widget;
};
