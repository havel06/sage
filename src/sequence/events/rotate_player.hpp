#pragma once

#include "../event.hpp"
#include "utils/direction.hpp"
#include "utils/string.hpp"

namespace Events
{

class Rotate_Player : public Event
{
public:
	Rotate_Player(Game_Facade&, Direction);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override {}
private:
	Direction m_direction;
};

}
