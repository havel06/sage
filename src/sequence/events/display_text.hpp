#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Display_Text : public Event
{
public:
	Display_Text(Game_Facade&, const String& message);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	String m_message;
	bool m_activated = false;
};

}
