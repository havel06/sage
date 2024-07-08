#include "change_sprite.hpp"
#include "utils/own_ptr.hpp"
#include "../events/change_sprite.hpp"

namespace Event_Factories {

Change_Sprite::Change_Sprite()
{
	register_parameter("entity", m_entity_name);
	register_parameter("sprite", m_sprite);
}

Own_Ptr<Event> Change_Sprite::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Change_Sprite>(facade, m_entity_name.value, m_sprite.value);
}

}
