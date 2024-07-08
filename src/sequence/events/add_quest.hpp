#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Add_Quest : public Event
{
public:
	Add_Quest(Game_Facade&, const String& id, const String& name, const String& description);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	String m_id;
	String m_name;
	String m_description;
	bool m_activated = false;
};

}
