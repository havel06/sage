#include "change_current_unit_sprite.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Change_Current_Unit_Sprite::Change_Current_Unit_Sprite(Game_Facade& facade, const Animated_Sprite& sprite) :
	Event{facade}
{
	m_sprite = sprite;
}

void Change_Current_Unit_Sprite::update(float)
{
	m_game_facade.combat_set_current_unit_sprite(m_sprite);
	m_activated = true;
}

bool Change_Current_Unit_Sprite::is_finished() const
{
	return m_activated;
}

void Change_Current_Unit_Sprite::reset()
{
	m_activated = false;
}

}
