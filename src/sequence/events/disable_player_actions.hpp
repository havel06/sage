#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Disable_Player_Actions : public Event
{
public:
	Disable_Player_Actions(Game_Facade&);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	bool m_activated = false;
};

}
