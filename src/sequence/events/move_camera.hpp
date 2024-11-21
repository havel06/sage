#pragma once

#include "../event.hpp"
#include "map/position.hpp"

namespace Events
{

class Move_Camera : public Event
{
public:
	Move_Camera(Game_Facade&, const Position& position);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override {}
private:
	Position m_position;
};

}
