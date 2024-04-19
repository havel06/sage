#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Echo : public Event
{
public:
	Echo(Game_Facade&, String&& message);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	String m_message;
	bool m_activated = false;
};

}
