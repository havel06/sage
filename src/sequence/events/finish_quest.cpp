#include "finish_quest.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Finish_Quest::Finish_Quest(Game_Facade& facade, const String& id) :
	Event(facade)
{
	m_id = id;
}

void Finish_Quest::update(float)
{
	m_game_facade.finish_quest(m_id);
	m_activated = true;
}

bool Finish_Quest::is_finished() const
{
	return m_activated;
}

void Finish_Quest::reset()
{
	m_activated = false;
}

}
