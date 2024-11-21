#pragma once

#include "../event.hpp"
#include "map/position.hpp"
#include "utils/vec2.hpp"

namespace Events
{

class Teleport_Player : public Event
{
public:
	Teleport_Player(Game_Facade&, const Position& position);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	Position m_position;
	bool m_activated = false;
};

}
