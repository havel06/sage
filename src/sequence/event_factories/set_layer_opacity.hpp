#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class Set_Layer_Opacity final : public Event_Factory
{
public:
	Set_Layer_Opacity();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Event_Parameter m_layer;
	Float_Event_Parameter m_opacity;
};

}
