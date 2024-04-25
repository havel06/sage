#include "combat_controller.hpp"
#include "combat.hpp"
#include <raylib/raylib.h>

Combat_Controller::Combat_Controller(Combat& combat) :
	m_combat{combat}
{
}

void Combat_Controller::go_down()
{

}

void Combat_Controller::go_up()
{

}

void Combat_Controller::go_right()
{

}

void Combat_Controller::go_left()
{

}

void Combat_Controller::enter()
{

}

void Combat_Controller::draw()
{
	const int padding = 50;
	int start_x = padding;
	const int height = 200;
	const int width = GetScreenWidth() - 2 * padding;
	int start_y =  GetScreenHeight() - height - padding;

	DrawRectangle(start_x, start_y, width, height, {0, 0, 0, 200});

	// FIXME - draw abilities
}
