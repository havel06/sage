#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Change_Map : public Event
{
public:
	Change_Map(String&& new_map);
	void update(Game_Facade&, float time_delta) override;
	bool is_finished() const override;
private:
	String m_new_map;
	bool m_activated = false;
};

}
