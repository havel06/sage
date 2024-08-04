#include "remove_sprite.hpp"
#include "game/game_facade.hpp"
#include "graphics/animated_sprite.hpp"

namespace Events
{

Remove_Sprite::Remove_Sprite(Game_Facade& facade, const String& entity_name) :
	Event{facade}
{
	m_entity_name = entity_name;
}

void Remove_Sprite::update(float)
{
	Animated_Sprite null_sprite;
	m_game_facade.set_entity_sprite(m_entity_name, null_sprite);
	m_activated = true;
}

bool Remove_Sprite::is_finished() const
{
	return m_activated;
}

void Remove_Sprite::reset()
{
	m_activated = false;
}

}
