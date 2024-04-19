#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Remove_Item : public Event
{
public:
	Remove_Item(String&& id, int count);
	void update(Game_Facade&, float time_delta) override;
	bool is_finished(Game_Facade&) const override;
	void reset() override;
private:
	String m_id;
	int m_count;
	bool m_activated = false;
};

}
