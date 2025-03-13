#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/target_selection_type_parameter.hpp"

namespace Event_Factories
{

class Select_Target final : public Event_Factory
{
public:
	Select_Target();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Target_Selection_Type_Parameter m_selection_type;
};

}
