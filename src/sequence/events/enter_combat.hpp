#pragma once

#include "../event.hpp"

namespace Events
{

class Enter_Combat : public Event
{
public:
	Enter_Combat(Game_Facade&);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	bool m_activated = false;
};

}
