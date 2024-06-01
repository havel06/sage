#pragma once

#include "../event.hpp"

namespace Events
{

class Delay : public Event
{
public:
	Delay(Game_Facade&, float seconds);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override {}
private:
	float m_time_active = 0;
	float m_delay_time;
};

}
