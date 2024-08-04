#include "remove_sprite.hpp"
#include "utils/own_ptr.hpp"
#include "../events/remove_sprite.hpp"

namespace Event_Factories {

Remove_Sprite::Remove_Sprite()
{
	register_parameter("entity", m_entity_name);
}

Own_Ptr<Event> Remove_Sprite::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Remove_Sprite>(facade, m_entity_name.value);
}

}
