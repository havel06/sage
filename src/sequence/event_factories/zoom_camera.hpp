#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"

namespace Event_Factories
{

class Zoom_Camera final : public Event_Factory
{
public:
	Zoom_Camera();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Int_Parameter m_zoom;
};

}
