#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"

namespace Event_Factories
{

class Set_Layer_Opacity final : public Event_Factory
{
public:
	Set_Layer_Opacity();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Parameter m_layer;
	Float_Parameter m_opacity;
};

}
