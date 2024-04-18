#pragma once

#include "../event.hpp"
#include "utils/string.hpp"
#include <raylib/raylib.h>

namespace Events
{

class Play_Sound : public Event
{
public:
	Play_Sound(Sound sound);
	void update(Game_Facade&, float time_delta) override;
	bool is_finished(Game_Facade&) const override;
	void reset() override;
private:
	Sound m_sound;
	bool m_activated = false;
};

}
