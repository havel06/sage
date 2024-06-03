#pragma once

#include "../event.hpp"
#include "utils/direction.hpp"
#include "utils/string.hpp"

namespace Events
{

class Rotate_Entity : public Event
{
public:
	Rotate_Entity(Game_Facade&, String&& entity_name, Direction);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override {}
private:

	String m_entity_name;
	Direction m_direction;
};

}
