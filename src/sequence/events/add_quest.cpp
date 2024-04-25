#include "add_quest.hpp"
#include "game_facade.hpp"

namespace Events
{

Add_Quest::Add_Quest(Game_Facade& facade, String&& name, String&& description) :
	Event(facade)
{
	m_name = (String&&)name;
	m_description = (String&&)description;
}

void Add_Quest::update(float)
{
	m_game_facade.add_quest(m_name, m_description);
	m_activated = true;
}

bool Add_Quest::is_finished() const
{
	return m_activated;
}

void Add_Quest::reset()
{
	m_activated = false;
}

}
