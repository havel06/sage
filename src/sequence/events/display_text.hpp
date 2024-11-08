#pragma once

#include "../event.hpp"
#include "utils/string.hpp"
#include "graphics/ui/formatted_text.hpp"

namespace Events
{

class Display_Text : public Event
{
public:
	Display_Text(Game_Facade&, const UI::Formatted_Text& message);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	UI::Formatted_Text m_message;
	bool m_activated = false;
};

}
