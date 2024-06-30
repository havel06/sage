#include "enter_combat.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Enter_Combat::Enter_Combat(Game_Facade& facade, Array<Character_Profile>&& enemies, Sequence& win_sequence) :
	Event{facade}, m_win_sequence{win_sequence}
{
	m_enemies = (Array<Character_Profile>&&)enemies;
}

void Enter_Combat::update(float)
{
	m_game_facade.enter_combat(m_enemies, m_win_sequence);
	m_activated = true;
}

bool Enter_Combat::is_finished() const
{
	return m_activated;
}

void Enter_Combat::reset()
{
	m_activated = false;
}

}
