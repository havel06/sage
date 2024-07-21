#pragma once

#include "../event.hpp"
#include "character_profile.hpp"
#include "utils/string.hpp"

namespace Events
{

class Add_To_Party : public Event
{
public:
	Add_To_Party(Game_Facade& facade, Resource_Handle<Character_Profile>);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	Resource_Handle<Character_Profile> m_profile;
	bool m_activated = false;
};

}
