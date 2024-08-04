#pragma once

#include "../event.hpp"
#include "utils/vec2.hpp"

namespace Events
{

class Move_Camera : public Event
{
public:
	Move_Camera(Game_Facade&, Vec2f position);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override {}
private:
	Vec2f m_position;
};

}
