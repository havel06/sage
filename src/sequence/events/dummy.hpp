#pragma once

#include "../event.hpp"

namespace Events
{

class Dummy : public Event
{
public:
	void update(Game_Facade&, float)
	{
	}

	bool is_finished() const
	{
		return true;
	}
};

}
