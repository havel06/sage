#pragma once

#include "../event.hpp"
#include "character_profile.hpp"
#include "utils/array.hpp"

namespace Events
{

class Enter_Combat : public Event
{
public:
	Enter_Combat(Game_Facade&, Array<Character_Profile>&& enemies);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	Array<Character_Profile> m_enemies;
	bool m_activated = false;
};

}
