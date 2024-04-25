#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Finish_Quest : public Event
{
public:
	Finish_Quest(Game_Facade&, String&& id);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	String m_id;
	bool m_activated = false;
};

}
