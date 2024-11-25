#include "set_layer_opacity.hpp"
#include "utils/own_ptr.hpp"
#include "../events/set_layer_opacity.hpp"

namespace Event_Factories {

Set_Layer_Opacity::Set_Layer_Opacity()
{
	register_parameter("layer", m_layer);
	register_parameter("opacity", m_opacity);
}

Own_Ptr<Event> Set_Layer_Opacity::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Set_Layer_Opacity>(facade, m_layer.value, m_opacity.value);
}

}
