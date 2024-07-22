#pragma once

#include "../event.hpp"
#include "utils/string.hpp"
#include "io/resource/resource_handle.hpp"

class Sequence;

namespace Events
{

class Activate_Sequence : public Event
{
public:
	Activate_Sequence(Game_Facade&, Resource_Handle<Sequence>);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	Resource_Handle<Sequence> m_sequence;
	bool m_activated = false;
};

}
