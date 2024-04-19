#pragma once

#include "../event.hpp"
#include "utils/vec2.hpp"

namespace Events
{

class Teleport_Player : public Event
{
public:
	Teleport_Player(Game_Facade&, Vec2i position);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	Vec2i m_position;
	bool m_activated = false;
};

}
