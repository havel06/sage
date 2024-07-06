#include "change_sprite.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Change_Sprite::Change_Sprite(Game_Facade& facade, String&& entity_name, const Animated_Sprite& sprite) :
	Event{facade}
{
	m_sprite = sprite;
	m_entity_name = (String&&)entity_name;
}

void Change_Sprite::update(float)
{
	m_game_facade.set_entity_sprite(m_entity_name, m_sprite);
	m_activated = true;
}

bool Change_Sprite::is_finished() const
{
	return m_activated;
}

void Change_Sprite::reset()
{
	m_activated = false;
}

}
