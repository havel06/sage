#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class Remove_Item final : public Event_Factory
{
public:
	Remove_Item();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Event_Parameter m_item_id;
	Int_Event_Parameter m_count;
};

}
