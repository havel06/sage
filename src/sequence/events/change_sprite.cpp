#include "change_sprite.hpp"
#include "game_facade.hpp"

namespace Events
{

Change_Sprite::Change_Sprite(String&& entity_name, const Sprite& sprite)
{
	m_sprite = sprite;
	m_entity_name = (String&&)entity_name;
}

void Change_Sprite::update(Game_Facade& facade, float)
{
	facade.set_entity_sprite(m_entity_name, m_sprite);
	m_activated = true;
}

bool Change_Sprite::is_finished(Game_Facade&) const
{
	return m_activated;
}

void Change_Sprite::reset()
{
	m_activated = false;
}

}
