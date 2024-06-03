#include "text_box.hpp"
#include "utils/log.hpp"
#include "utils/minmax.hpp"

bool Text_Box::contains_message() const
{
	return !m_messages.empty();
}

String Text_Box::get_displayed_message() const
{
	assert(contains_message());
	return m_messages[m_current_message];
}

int Text_Box::get_displayed_character_count() const
{
	assert(contains_message());
	const float time_per_character = 0.02;
	return min((int)(m_time_shown / time_per_character), m_messages[m_current_message].length());
}

void Text_Box::push_message(String&& message)
{
	m_messages.push_back((String&&)message);
}

void Text_Box::advance()
{
	m_current_message++;
	m_time_shown = 0;

	// Are we at the end yet?
	if (m_current_message >= m_messages.size()) {
		m_messages.clear();
		m_current_message = 0;
	}
}

void Text_Box::update(float time_delta)
{
	if (contains_message())
		m_time_shown += time_delta;
}
