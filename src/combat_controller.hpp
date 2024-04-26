#pragma once

class Combat;

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
	void go_down();
	void go_up();
	void go_right();
	void go_left();
	void enter();
	void draw();
private:
	void draw_abilities();
	void draw_selected_enemy();
	void fix_selected_ability_index();

	const int m_margin = 50;
	const int m_height = 200;

	int m_selected_ability = 0;
	int m_selected_enemy = 0;
	Combat_Controller_State m_state = Combat_Controller_State::selecting_ability;
	Combat& m_combat;
};
