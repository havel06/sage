#include "combat_saveloader.hpp"
#include "combat/combat.hpp"
#include "combat/combat_unit.hpp"
#include "io/resource/sequence_manager.hpp"
#include "io/resource/character_profile_manager.hpp"
#include "utils/json.hpp"
#include "io/json_types.hpp"
#include "game/game_logic.hpp"

Combat_Saveloader::Combat_Saveloader(
		Combat& combat,
		Sequence_Manager& seq_mgr,
		Character_Profile_Manager& character_mgr,
		Texture_Manager& texture_manager,
		Game_Logic& logic,
		const String& project_dir) :
	m_combat{combat},
	m_seq_manager{seq_mgr},
	m_character_manager{character_mgr},
	m_texture_manager{texture_manager},
	m_logic{logic},
	m_project_dir{project_dir}
{
}

JSON::Object Combat_Saveloader::save()
{
	assert(m_combat.is_active());

	Battle& battle = m_combat.get_battle();
	JSON::Object json;

	// Sequences
	String win_sequence_path =
		get_relative_path(battle.get_description().win_sequence.get_path(), m_project_dir);
	String lose_sequence_path =
		get_relative_path(battle.get_description().lose_sequence.get_path(), m_project_dir);

	json.add("win_sequence", win_sequence_path.data());
	json.add("lose_sequence", lose_sequence_path.data());
	json.add(
		"background",
		JSON_Types::serialise_animated_sprite(
			battle.get_description().background,
			m_project_dir
		)
	);

	json.add("layout",
		JSON_Types::serialise_battle_units_layout(battle.get_description().units_layout)
	);

	// Serialise units
	auto serialise_unit = [&](const Combat_Unit& unit) -> JSON::Value {
		JSON::Object unit_json;
		String path = get_relative_path(unit.character.get_path(), m_project_dir);
		unit_json.add("character", path.data());
		unit_json.add("hp", unit.get_hp());
		return unit_json;
	};

	JSON::Array heroes;
	for (int i = 0; i < battle.get_hero_count(); i++)
		heroes.add(serialise_unit(battle.get_hero(i)));

	JSON::Array enemies;
	for (int i = 0; i < battle.get_enemy_count(); i++)
		enemies.add(serialise_unit(battle.get_enemy(i)));

	json.add("heroes", move(heroes));
	json.add("enemies", move(enemies));

	// Side of the current turn
	json.add("current_turn_side", combat_unit_side_to_string(battle.get_current_side()).data());

	return json;
}

void Combat_Saveloader::load(const JSON::Object_View& json)
{
	auto parse_unit = [&](const JSON::Object_View& unit_json) -> Battle_Unit_Definition {
		Resource_Handle<Character_Profile> profile =
			m_character_manager.get(unit_json["character"].as_string(""), false);

		return Battle_Unit_Definition{profile, unit_json.get("hp").as_int(1)};
	};

	Array<Battle_Unit_Definition> enemies;
	json.get("enemies").as_array().for_each([&](const JSON::Value_View& value){
		enemies.push_back(parse_unit(value.as_object()));
	});

	Array<Battle_Unit_Definition> heroes;
	json.get("heroes").as_array().for_each([&](const JSON::Value_View& value){
		heroes.push_back(parse_unit(value.as_object()));
	});

	Resource_Handle<Sequence> win_seq =
		m_seq_manager.get(json.get("win_sequence").as_string(""), false);

	Resource_Handle<Sequence> lose_seq =
		m_seq_manager.get(json.get("lose_sequence").as_string(""), false);

	Animated_Sprite background = 
		JSON_Types::parse_animated_sprite(json.get("background").as_object(), m_texture_manager);

	Battle_Units_Layout layout =
		JSON_Types::parse_battle_units_layout(json.get("layout").as_object());

	Combat_Unit_Side starting_side =
		combat_unit_side_from_string(
			json.get("current_turn_side").as_string("hero")
		).value_or(Combat_Unit_Side::hero);

	Battle_Description description {
		.heroes = move(heroes),
		.enemies = move(enemies),
		.win_sequence = win_seq,
		.lose_sequence = lose_seq,
		.background = move(background),
		.units_layout = move(layout),
		.starting_side = starting_side
	};

	m_logic.enter_combat(description);
}
