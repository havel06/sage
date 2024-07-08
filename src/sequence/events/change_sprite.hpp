#pragma once

#include "../event.hpp"
#include "utils/string.hpp"
#include "graphics/animated_sprite.hpp"

namespace Events
{

class Change_Sprite : public Event
{
public:
	Change_Sprite(Game_Facade&, const String& entity_name, const Animated_Sprite&);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	String m_entity_name;
	Animated_Sprite m_sprite;
	bool m_activated = false;
};

}
