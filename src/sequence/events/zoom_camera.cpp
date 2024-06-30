#include "zoom_camera.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Zoom_Camera::Zoom_Camera(Game_Facade& facade, int amount) :
	Event{facade}
{
	m_amount = amount;
}

void Zoom_Camera::update(float)
{
	m_game_facade.zoom_camera(m_amount);
	m_activated = true;
}

bool Zoom_Camera::is_finished() const
{
	return m_activated;
}

void Zoom_Camera::reset()
{
	m_activated = false;
}

}
