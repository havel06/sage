#pragma once

#include "../event.hpp"
#include "utils/vec2.hpp"
#include "utils/string.hpp"

namespace Events
{

class Move_Entity : public Event
{
public:
	Move_Entity(Game_Facade&, String&& entity_name, Vec2i position);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override {}
private:

	String m_entity_name;
	Vec2i m_position;
};

}
