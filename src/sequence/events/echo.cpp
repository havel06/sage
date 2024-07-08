#include "echo.hpp"
#include "utils/log.hpp"

namespace Events
{

Echo::Echo(Game_Facade& game_facade, const String& message) :
	Event{game_facade}
{
	m_message = message;
}

void Echo::update(float)
{
	SG_INFO("Echo: %s", m_message.data());
	m_activated = true;	
}

bool Echo::is_finished() const
{
	return m_activated;
}

void Echo::reset()
{
	m_activated = false;
}

}
