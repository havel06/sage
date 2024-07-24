#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Change_Current_Unit_HP : public Event
{
public:
	Change_Current_Unit_HP(Game_Facade&, int amount);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	int m_amount;
	bool m_activated = false;
};

}
