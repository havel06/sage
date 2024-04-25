#include "quest_log.hpp"
#include "utils/log.hpp"


void Quest_Log::add_quest(Quest&& quest)
{
	m_quests.push_back((Quest&&)quest);
}

void Quest_Log::remove_quest(const String& id)
{
	for (int i = 0; i < m_quests.size(); i++) {
		if (m_quests[i].id == id) {
			m_quests.remove(i);
			return;
		}
	}

	SG_ERROR("Could not find quest \"%s\"", id.data());
}

int Quest_Log::get_quest_count() const
{
	return m_quests.size();
}

const Quest& Quest_Log::get_quest(int index) const
{
	return m_quests[index];
}
