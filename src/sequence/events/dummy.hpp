#pragma once

#include "../event.hpp"

namespace Events
{

class Dummy : public Event
{
public:
	void update(Game_Facade&, float) override
	{
	}

	bool is_finished(Game_Facade&) const override
	{
		return true;
	}

	void reset() override
	{
	}
};

}
