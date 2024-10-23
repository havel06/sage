#include "reset_current_unit_sprite.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Reset_Current_Unit_Sprite::Reset_Current_Unit_Sprite(Game_Facade& facade) :
	Event{facade}
{
}

void Reset_Current_Unit_Sprite::update(float)
{
	m_game_facade.combat_reset_current_unit_sprite();
	m_activated = true;
}

bool Reset_Current_Unit_Sprite::is_finished() const
{
	return m_activated;
}

void Reset_Current_Unit_Sprite::reset()
{
	m_activated = false;
}

}
