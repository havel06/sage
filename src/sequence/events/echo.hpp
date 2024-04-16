#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Echo : public Event
{
public:
	Echo(String&& message);
	void update(Game_Facade&, float time_delta) override;
	bool is_finished(Game_Facade&) const override;
	void reset() override;
private:
	String m_message;
	bool m_activated = false;
};

}
