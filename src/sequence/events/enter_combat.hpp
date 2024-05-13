#pragma once

#include "../event.hpp"
#include "character_profile.hpp"
#include "utils/array.hpp"

class Sequence;

namespace Events
{

class Enter_Combat : public Event
{
public:
	Enter_Combat(Game_Facade&, Array<Character_Profile>&& enemies, Sequence& win_sequence);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	Array<Character_Profile> m_enemies;
	Sequence& m_win_sequence;
	bool m_activated = false;
};

}
