#include "display_text.hpp"
#include "game_facade.hpp"
#include "utils/log.hpp"

namespace Events
{

Display_Text::Display_Text(String&& message)
{
	m_message = (String&&)message;
}

void Display_Text::update(Game_Facade& facade, float)
{
	if (!m_activated) {
		facade.display_text(String{m_message});
		m_activated = true;
	}
}

bool Display_Text::is_finished(Game_Facade& facade) const
{
	return !facade.is_text_box_shown();
}

void Display_Text::reset()
{
	m_activated = false;
}

}
