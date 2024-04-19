#pragma once

#include "../event.hpp"

namespace Events
{

class Dummy : public Event
{
public:
	Dummy(Game_Facade& facade) : Event{facade}
	{
	}

	void update(float) override
	{
	}

	bool is_finished() const override
	{
		return true;
	}

	void reset() override
	{
	}
};

}
