#pragma once
#include "utils/string.hpp"
#include "graphics/ui/widget.hpp"

// fwd
class Combat;
class GUI_Loader;

enum class Combat_Controller_State
{
	selecting_ability,
	selecting_enemy,
};

// FIXME - refactor this after switching to new UI system
// FIXME - move some rendering (future effects and such) into cobmat_renderer

class Combat_Controller
{
public:
	Combat_Controller(Combat&);
	void load(GUI_Loader&, const String& project_root);
	void input_direction(Direction);
	void enter();
	void draw();
private:
	void draw_abilities();
	void draw_selected_enemy();

	int m_selected_ability = 0; // FIXME - remove
	int m_selected_enemy = 0;
	Combat_Controller_State m_state = Combat_Controller_State::selecting_ability;
	Combat& m_combat;

	UI::Widget_Ptr m_menu_widget;
};
