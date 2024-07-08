#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Change_Map : public Event
{
public:
	Change_Map(Game_Facade& facade, const String& new_map);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	String m_new_map;
	bool m_activated = false;
};

}
