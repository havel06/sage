#include "text_box.hpp"

bool Text_Box::contains_message() const
{
	return !m_messages.empty();
}

const String& Text_Box::get_displayed_message() const
{
	assert(contains_message());
	return m_messages[m_current_message];
}

void Text_Box::push_message(String&& message)
{
	m_messages.push_back((String&&)message);
}

void Text_Box::advance()
{
	m_current_message++;

	// Are we at the end yet?
	if (m_current_message >= m_messages.size()) {
		m_messages.clear();
		m_current_message = 0;
	}
}
