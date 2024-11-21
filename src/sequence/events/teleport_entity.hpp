#pragma once

#include "../event.hpp"
#include "map/position.hpp"
#include "utils/vec2.hpp"
#include "utils/string.hpp"

namespace Events
{

class Teleport_Entity : public Event
{
public:
	Teleport_Entity(Game_Facade&, const String& name, const Position& position);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	String m_name;
	Position m_position;
	bool m_activated = false;
};

}
