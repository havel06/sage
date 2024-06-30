#pragma once

#include "../event.hpp"
#include "character_profile.hpp"
#include "utils/array.hpp"
#include "combat/battle_desc.hpp"

class Sequence;

namespace Events
{

class Enter_Combat : public Event
{
public:
	Enter_Combat(Game_Facade&, Battle_Description&& description);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	Battle_Description m_description;
	bool m_activated = false;
};

}
