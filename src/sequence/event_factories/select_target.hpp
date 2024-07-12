#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class Select_Target final : public Event_Factory
{
public:
	Select_Target();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Target_Selection_Type_Event_Parameter m_selection_type;
};

}
