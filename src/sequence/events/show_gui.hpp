#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Show_GUI : public Event
{
public:
	Show_GUI(Game_Facade&, const String& filename);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	String m_filename;
	bool m_activated = false;
};

}
