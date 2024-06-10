#pragma once

class Quest_Log;

namespace JSON {
	class Array;
	class Array_View;
}

class Quest_Saveloader
{
public:
	Quest_Saveloader(Quest_Log&);
	JSON::Array save();
	void load(const JSON::Array_View&);
private:
	Quest_Log& m_quest_log;
};
