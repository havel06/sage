#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Give_Item : public Event
{
public:
	Give_Item(Game_Facade&, String&& id, int count);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	String m_id;
	int m_count;
	bool m_activated = false;
};

}
