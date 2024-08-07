#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Teleport_Camera_To_Player : public Event
{
public:
	Teleport_Camera_To_Player(Game_Facade&);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	bool m_activated = false;
};

}
