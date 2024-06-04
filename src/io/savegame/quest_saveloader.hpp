#pragma once

class Quest_Log;
struct cJSON;

class Quest_Saveloader
{
public:
	Quest_Saveloader(Quest_Log&);
	cJSON* save();
	void load(const cJSON*);
private:
	Quest_Log& m_quest_log;
};
