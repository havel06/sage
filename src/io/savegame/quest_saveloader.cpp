#include "quest_saveloader.hpp"
#include "quest/quest_log.hpp"
#include "utils/json.hpp"

Quest_Saveloader::Quest_Saveloader(Quest_Log& quest_log) :
	m_quest_log{quest_log}
{
}

JSON::Array Quest_Saveloader::save()
{
	JSON::Array json;

	for (int i = 0; i < m_quest_log.get_quest_count(); i++) {
		const Quest& quest = m_quest_log.get_quest(i);
		JSON::Object quest_json;
		quest_json.add("id", JSON::Value(quest.id.data()));
		quest_json.add("name", JSON::Value(quest.name.data()));
		quest_json.add("description", JSON::Value(quest.description.data()));
		json.add((JSON::Value&&)quest_json);
	}

	return json;
}

void Quest_Saveloader::load(const JSON::Array_View& json)
{
	m_quest_log.clear();

	json.for_each([&](const JSON::Value_View& value){
		JSON::Object_View quest_json = value.as_object();
		Quest quest;
		quest.id = quest_json["id"].as_string();
		quest.name = quest_json["name"].as_string();
		quest.description = quest_json["description"].as_string();
		m_quest_log.add_quest((Quest&&)quest);
	});
}
