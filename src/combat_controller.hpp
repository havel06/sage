#pragma once

class Combat;

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
	Combat& m_combat;
	int m_selected_ability = 0;
};
