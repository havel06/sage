#include "zoom_camera.hpp"
#include "utils/own_ptr.hpp"
#include "../events/zoom_camera.hpp"

namespace Event_Factories {

Zoom_Camera::Zoom_Camera()
{
	register_parameter("zoom", m_zoom);
}

Own_Ptr<Event> Zoom_Camera::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Zoom_Camera>(facade, m_zoom.value);
}

}
