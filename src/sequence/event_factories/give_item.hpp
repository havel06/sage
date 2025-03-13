#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/string_parameter.hpp"
#include "templating/parameters/int_parameter.hpp"

namespace Event_Factories
{

class Give_Item final : public Event_Factory
{
public:
	Give_Item();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Parameter m_item_id;
	Int_Parameter m_count;
};

}
