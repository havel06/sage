#include "echo.hpp"
#include "utils/log.hpp"

namespace Events
{

Echo::Echo(String&& message)
{
	m_message = message;
}

void Echo::update(Game_Facade&, float)
{
	SG_INFO("Echo: %s", m_message.data());
	m_activated = true;	
}

bool Echo::is_finished(Game_Facade&) const
{
	return m_activated;
}

void Echo::reset()
{
	m_activated = false;
}

}
