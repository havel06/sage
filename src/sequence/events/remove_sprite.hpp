#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Remove_Sprite : public Event
{
public:
	Remove_Sprite(Game_Facade&, const String& entity_name);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	String m_entity_name;
	bool m_activated = false;
};

}
