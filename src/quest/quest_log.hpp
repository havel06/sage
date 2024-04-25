#pragma once

#include "quest.hpp"
#include "utils/array.hpp"

class Quest_Log
{
public:
	void add_quest(Quest&&);
	void remove_quest(const String& name);
private:
	Array<Quest> m_quests;
};
