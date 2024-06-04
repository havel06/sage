#include "quest_saveloader.hpp"
#include "cJSON.h"
#include "quest/quest_log.hpp"

Quest_Saveloader::Quest_Saveloader(Quest_Log& quest_log) :
	m_quest_log{quest_log}
{
}

cJSON* Quest_Saveloader::save()
{
	cJSON* json = cJSON_CreateArray();

	for (int i = 0; i < m_quest_log.get_quest_count(); i++) {
		const Quest& quest = m_quest_log.get_quest(i);
		cJSON* quest_json = cJSON_CreateObject();
		cJSON_AddItemToObject(quest_json, "id", cJSON_CreateString(quest.id.data()));
		cJSON_AddItemToObject(quest_json, "name", cJSON_CreateString(quest.name.data()));
		cJSON_AddItemToObject(quest_json, "description", cJSON_CreateString(quest.description.data()));
		cJSON_AddItemToArray(json, quest_json);
	}

	return json;
}

void Quest_Saveloader::load(const cJSON* json)
{
	m_quest_log.clear();

	const cJSON* quest_json = nullptr;
	cJSON_ArrayForEach(quest_json, json) {
		Quest quest;
		quest.id = cJSON_GetObjectItem(quest_json, "id")->valuestring;
		quest.name = cJSON_GetObjectItem(quest_json, "name")->valuestring;
		quest.description = cJSON_GetObjectItem(quest_json, "description")->valuestring;
		m_quest_log.add_quest((Quest&&)quest);
	}
}
