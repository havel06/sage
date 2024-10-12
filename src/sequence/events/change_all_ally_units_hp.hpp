#pragma once

#include "../event.hpp"

namespace Events
{

class Change_All_Ally_Units_HP : public Event
{
public:
	Change_All_Ally_Units_HP(Game_Facade&, int amount);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	int m_amount;
	bool m_activated = false;
};

}
