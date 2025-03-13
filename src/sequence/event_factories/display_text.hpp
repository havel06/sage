#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/formatted_text_parameter.hpp"

namespace Event_Factories
{

class Display_Text final : public Event_Factory
{
public:
	Display_Text();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Formatted_Text_Parameter m_message;
};

}
