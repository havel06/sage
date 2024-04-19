#pragma once

#include "../event.hpp"
#include "utils/string.hpp"
#include <raylib/raylib.h>

namespace Events
{

class Play_Sound : public Event
{
public:
	Play_Sound(Game_Facade&, Sound sound);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	Sound m_sound;
	bool m_activated = false;
};

}
