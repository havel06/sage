#include "character_profile_loader.hpp"
#include "ability.hpp"
#include "utils/file.hpp"
#include "cJSON.h"
#include "resource_manager.hpp"
#include "cjson_types.hpp"

Character_Profile_Loader::Character_Profile_Loader(Resource_Manager& res_mgr) :
	m_resource_manager{res_mgr}
{
}

Character_Profile Character_Profile_Loader::load(const char* file_path)
{
	String content = read_file_to_str(file_path);
	cJSON* json = cJSON_Parse(content.data());

	Character_Profile profile;

	profile.name = cJSON_GetObjectItem(json, "name")->valuestring;

	const cJSON* sprite_down_json  = cJSON_GetObjectItem(json, "sprite_down");
	const cJSON* sprite_up_json    = cJSON_GetObjectItem(json, "sprite_up");
	const cJSON* sprite_left_json  = cJSON_GetObjectItem(json, "sprite_left");
	const cJSON* sprite_right_json = cJSON_GetObjectItem(json, "sprite_right");

	profile.sprite_down  = cJSON_Types::parse_sprite(sprite_down_json,  m_resource_manager);
	profile.sprite_up    = cJSON_Types::parse_sprite(sprite_up_json,    m_resource_manager);
	profile.sprite_left  = cJSON_Types::parse_sprite(sprite_left_json,  m_resource_manager);
	profile.sprite_right = cJSON_Types::parse_sprite(sprite_right_json, m_resource_manager);

	const cJSON* character_size = cJSON_GetObjectItem(json, "size");
	if (character_size) {
		profile.size.x = cJSON_GetObjectItem(character_size, "x")->valuedouble;
		profile.size.y = cJSON_GetObjectItem(character_size, "y")->valuedouble;
	}

	const cJSON* move_speed = cJSON_GetObjectItem(json, "move_speed");
	if (move_speed) {
		profile.move_speed = move_speed->valuedouble;
	}

	const cJSON* abilites = cJSON_GetObjectItem(json, "abilities");
	const cJSON* ability_json;
	cJSON_ArrayForEach(ability_json, abilites) {
		profile.abilities.push_back(load_ability(ability_json));
	}

	profile.max_hp = cJSON_GetObjectItem(json, "max_hp")->valueint;

	cJSON_Delete(json);

	return profile;
}

Ability Character_Profile_Loader::load_ability(const cJSON* ability_json)
{
	Ability ability;
	ability.name = cJSON_GetObjectItem(ability_json, "name")->valuestring;
	ability.damage = cJSON_GetObjectItem(ability_json, "damage")->valueint;
	return ability;
}
