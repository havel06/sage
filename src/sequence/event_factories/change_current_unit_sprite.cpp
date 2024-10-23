#include "change_current_unit_sprite.hpp"
#include "utils/own_ptr.hpp"
#include "../events/change_current_unit_sprite.hpp"

namespace Event_Factories {

Change_Current_Unit_Sprite::Change_Current_Unit_Sprite()
{
	register_parameter("sprite", m_sprite);
}

Own_Ptr<Event> Change_Current_Unit_Sprite::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Change_Current_Unit_Sprite>(facade, m_sprite.value);
}

}
