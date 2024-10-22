#pragma once

// fwd
class Texture_Manager;
class Sequence_Manager;
template<typename T> class Array;
struct Combat_Stances;
struct Ability;
struct Character_Profile;
namespace JSON {
	class Object_View;
	class Array_View;
}

class Character_Profile_Loader
{
public:
	Character_Profile_Loader(Texture_Manager&, Sequence_Manager&);
	Character_Profile load(const char* file_path);
private:
	Ability load_ability(const JSON::Object_View& ability_json);
	Array<Combat_Stances> parse_stances(const JSON::Array_View& json);

	Texture_Manager& m_texture_manager;
	Sequence_Manager& m_sequence_manager;
};
