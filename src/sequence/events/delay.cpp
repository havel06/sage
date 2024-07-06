#include "delay.hpp"

namespace Events
{

Delay::Delay(Game_Facade& game_facade, float time) :
	Event{game_facade}
{
	m_delay_time = time;
}

void Delay::update(float time_delta)
{
	m_time_active += time_delta;
}

bool Delay::is_finished() const
{
	return m_time_active >= m_delay_time;
}

void Delay::reset()
{
	m_time_active = 0;
}

}
