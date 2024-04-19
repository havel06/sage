#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

class Sequence;

namespace Events
{

class Activate_Sequence : public Event
{
public:
	Activate_Sequence(Game_Facade&, Sequence&);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	Sequence& m_sequence;
	bool m_activated = false;
};

}
