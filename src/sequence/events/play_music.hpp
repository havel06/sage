#pragma once

#include "../event.hpp"
#include "utils/string.hpp"
#include <raylib/raylib.h>

namespace Events
{

class Play_Music : public Event
{
public:
	Play_Music(Sound);
	void update(Game_Facade&, float time_delta) override;
	bool is_finished(Game_Facade&) const override;
	void reset() override;
private:
	Sound m_music;
	bool m_activated = false;
};

}
