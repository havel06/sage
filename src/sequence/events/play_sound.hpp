#pragma once

#include "../event.hpp"
#include "io/resource/resource_handle.hpp"
#include "utils/string.hpp"
#include <raylib/raylib.h>

namespace Events
{

class Play_Sound : public Event
{
public:
	Play_Sound(Game_Facade&, Resource_Handle<Sound> sound);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	Resource_Handle<Sound> m_sound;
	bool m_activated = false;
};

}
