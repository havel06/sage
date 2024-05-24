#pragma once

#include "../event.hpp"

namespace Events
{

class Zoom_Camera : public Event
{
public:
	Zoom_Camera(Game_Facade&, int amount);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	int m_amount;
	bool m_activated = false;
};

}
