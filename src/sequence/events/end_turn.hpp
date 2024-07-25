#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class End_Turn : public Event
{
public:
	End_Turn(Game_Facade&);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	bool m_activated = false;
};

}
