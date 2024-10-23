#pragma once

#include "../event.hpp"
#include "graphics/animated_sprite.hpp"

namespace Events
{

class Change_Current_Unit_Sprite : public Event
{
public:
	Change_Current_Unit_Sprite(Game_Facade&, const Animated_Sprite&);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	Animated_Sprite m_sprite;
	bool m_activated = false;
};

}
