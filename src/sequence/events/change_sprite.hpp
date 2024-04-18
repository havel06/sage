#pragma once

#include "../event.hpp"
#include "utils/string.hpp"
#include "graphics/sprite.hpp"

namespace Events
{

class Change_Sprite : public Event
{
public:
	Change_Sprite(String&& entity_name, const Sprite&);
	void update(Game_Facade&, float time_delta) override;
	bool is_finished(Game_Facade&) const override;
	void reset() override;
private:
	String m_entity_name;
	Sprite m_sprite;
	bool m_activated = false;
};

}
