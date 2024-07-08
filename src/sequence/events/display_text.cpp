#include "display_text.hpp"
#include "game/game_facade.hpp"
#include "utils/log.hpp"

namespace Events
{

Display_Text::Display_Text(Game_Facade& facade, const String& message) :
	Event(facade)
{
	m_message = message;
}

void Display_Text::update(float)
{
	if (!m_activated) {
		m_game_facade.display_text(String{m_message});
		m_activated = true;
	}
}

bool Display_Text::is_finished() const
{
	return !m_game_facade.is_text_box_shown();
}

void Display_Text::reset()
{
	m_activated = false;
}

}
