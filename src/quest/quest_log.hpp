#pragma once

#include "quest.hpp"
#include "utils/array.hpp"

class Quest_Log
{
public:
	void add_quest(Quest&&);
	void remove_quest(const String& id);
	int get_quest_count() const;
	const Quest& get_quest(int index) const;
private:
	Array<Quest> m_quests;
};
