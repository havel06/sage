#pragma once

#include "../event.hpp"
#include "map/position.hpp"
#include "utils/vec2.hpp"
#include "utils/string.hpp"

namespace Events
{

class Move_Entity : public Event
{
public:
	Move_Entity(Game_Facade&, const String& entity_name, const Position& position);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override {}
private:
	String m_entity_name;
	Position m_position;
};

}
