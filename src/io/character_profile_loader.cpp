#include "character_profile_loader.hpp"
#include "ability.hpp"
#include "combat/stances.hpp"
#include "io/resource/sequence_manager.hpp"
#include "utils/file.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include "utils/move.hpp"
#include "json_types.hpp"
#include "character_profile.hpp"

Character_Profile_Loader::Character_Profile_Loader(Texture_Manager& tex_mgr, Sequence_Manager& seq_mgr) :
	m_texture_manager{tex_mgr},
	m_sequence_manager{seq_mgr}
{
}

Character_Profile Character_Profile_Loader::load(const char* file_path)
{
	JSON::Object json = JSON::Object::from_file(file_path);
	JSON::Object_View json_view = json.get_view();

	Character_Profile profile;

	profile.name = json_view["name"].as_string("Unknown");
	profile.filename = file_path;

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
		profile.size.x = character_size["x"].as_float(1);
		profile.size.y = character_size["y"].as_float(1);
	}

	if (json_view.has("move_speed")) {
		profile.move_speed = json_view["move_speed"].as_float(CHARACTER_DEFAULT_SPEED);
	}

	if (json_view.has("abilities")) {
		JSON::Array_View abilites = json_view["abilities"].as_array();
		abilites.for_each([&](const JSON::Value_View& ability_json){
			profile.abilities.push_back(load_ability(ability_json.as_object()));
		});
	}

	profile.max_hp = json_view["max_hp"].as_int(CHARACTER_DEFAULT_HP);

	return profile;
}

Ability Character_Profile_Loader::load_ability(const JSON::Object_View& ability_json)
{
	String name = ability_json["name"].as_string("Unknown");
	const char* sequence_filename = ability_json["sequence"].as_string("");

	if (strlen(sequence_filename) == 0) {
		SG_ERROR("Ability sequence not set.");
	}

	Resource_Handle<Sequence> sequence = m_sequence_manager.get(sequence_filename, false);
	Array<Combat_Stances> stances = parse_stances(ability_json.get("stances").as_array());

	return Ability {
		.name = move(name),
		.sequence = sequence,
		.stances = move(stances)
	};
}

Array<Combat_Stances> Character_Profile_Loader::parse_stances(const JSON::Array_View& json)
{
	Array<Combat_Stances> result;

	json.for_each([&](const JSON::Value_View& value){
		JSON::Object_View stances_json = value.as_object();
		Combat_Stances stances;

		if (stances_json.has("offense")) {
			stances.offense = stances_json.get("offense").as_float(0);
		}

		if (stances_json.has("defense")) {
			stances.defense = stances_json.get("defense").as_float(0);
		}

		if (stances_json.has("aid")) {
			stances.aid = stances_json.get("aid").as_float(0);
		}

		result.push_back(stances);
	});

	return result;
}
