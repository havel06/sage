#pragma once

#include "../event.hpp"
#include "graphics/game_ui/layout.hpp"

namespace Events
{

class Hide_GUI : public Event
{
public:
	Hide_GUI(Game_Facade&);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	bool m_activated = false;
};

}
