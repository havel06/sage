#pragma once

#include "../event.hpp"
#include "utils/vec2.hpp"
#include "utils/string.hpp"

namespace Events
{

class Teleport_Entity : public Event
{
public:
	Teleport_Entity(String&& name, Vec2i position);
	void update(Game_Facade&, float time_delta) override;
	bool is_finished(Game_Facade&) const override;
	void reset() override;
private:
	String m_name;
	Vec2i m_position;
	bool m_activated = false;
};

}
