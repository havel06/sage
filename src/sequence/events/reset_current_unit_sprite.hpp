#pragma once

#include "../event.hpp"
#include "graphics/animated_sprite.hpp"

namespace Events
{

class Reset_Current_Unit_Sprite : public Event
{
public:
	Reset_Current_Unit_Sprite(Game_Facade&);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	bool m_activated = false;
};

}
