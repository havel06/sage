#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

class GUI_Loader;

namespace Event_Factories
{

class Show_GUI final : public Event_Factory
{
public:
	Show_GUI();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Event_Parameter m_widget_filename;
};

}
