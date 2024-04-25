#pragma once

class Combat;

enum class Combat_Controller_State
{
	selecting_ability,
	selecting_enemy,
	waiting_for_enemy_turn,
};

// FIXME - refactor this after switching to new UI system

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
	void fix_selected_ability_index();

	const int m_margin = 50;
	const int m_height = 200;

	Combat& m_combat;
	int m_selected_ability = 0;
};
