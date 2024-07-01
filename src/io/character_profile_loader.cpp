#include "character_profile_loader.hpp"
#include "ability.hpp"
#include "utils/file.hpp"
#include "utils/json.hpp"
#include "json_types.hpp"

Character_Profile_Loader::Character_Profile_Loader(Texture_Manager& tex_mgr) :
	m_texture_manager{tex_mgr}
{
}

Character_Profile Character_Profile_Loader::load(const char* file_path)
{
	JSON::Object json = JSON::Object::from_file(file_path);
	JSON::Object_View json_view = json.get_view();

	Character_Profile profile;

	profile.name = json_view["name"].as_string();

	profile.sprite_down  = JSON_Types::parse_animated_sprite(json_view["sprite_down"].as_object(),  m_texture_manager);
	profile.sprite_up    = JSON_Types::parse_animated_sprite(json_view["sprite_up"].as_object(),    m_texture_manager);
	profile.sprite_left  = JSON_Types::parse_animated_sprite(json_view["sprite_left"].as_object(),  m_texture_manager);
	profile.sprite_right = JSON_Types::parse_animated_sprite(json_view["sprite_right"].as_object(), m_texture_manager);

	if (json_view.has("sprite_move_down")) {
		profile.sprite_move_down =
			JSON_Types::parse_animated_sprite(json_view["sprite_move_down"].as_object(),  m_texture_manager);
	} else {
		profile.sprite_move_down = profile.sprite_down;
	}

	if (json_view.has("sprite_move_up")) {
		profile.sprite_move_up =
			JSON_Types::parse_animated_sprite(json_view["sprite_move_up"].as_object(),  m_texture_manager);
	} else {
		profile.sprite_move_up = profile.sprite_up;
	}

	if (json_view.has("sprite_move_left")) {
		profile.sprite_move_left =
			JSON_Types::parse_animated_sprite(json_view["sprite_move_left"].as_object(),  m_texture_manager);
	} else {
		profile.sprite_move_left = profile.sprite_left;
	}

	if (json_view.has("sprite_move_right")) {
		profile.sprite_move_right =
			JSON_Types::parse_animated_sprite(json_view["sprite_move_right"].as_object(),  m_texture_manager);
	} else {
		profile.sprite_move_right = profile.sprite_right;
	}

	if (json_view.has("size")) {
		const JSON::Object_View character_size = json_view["size"].as_object();
		profile.size.x = character_size["x"].as_float();
		profile.size.y = character_size["y"].as_float();
	}

	if (json_view.has("move_speed")) {
		profile.move_speed = json_view["move_speed"].as_float();
	}

	if (json_view.has("abilities")) {
		JSON::Array_View abilites = json_view["abilities"].as_array();
		abilites.for_each([&](const JSON::Value_View& ability_json){
			profile.abilities.push_back(load_ability(ability_json.as_object()));
		});
	}

	profile.max_hp = json_view["max_hp"].as_int();

	return profile;
}

Ability Character_Profile_Loader::load_ability(const JSON::Object_View& ability_json)
{
	Ability ability;
	ability.name = ability_json["name"].as_string();
	ability.damage = ability_json["damage"].as_int();
	return ability;
}
