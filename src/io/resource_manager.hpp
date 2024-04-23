#pragma once
#include "utils/string.hpp"
#include "utils/table.hpp"
#include "utils/pool_table.hpp"
#include "sequence/sequence.hpp"
#include "map/map.hpp"
#include "character_profile.hpp"
#include <raylib/raylib.h>

class Sequence_Loader;

class Resource_Manager
{
public:
	Resource_Manager(Sequence_Loader&, const String& asset_path);

	Texture get_texture(const char* filename, bool absolute_path = false);
	Sound get_sound(const char* filename);
	Sequence& get_sequence(const char*, bool absolute_path = false);
	Map get_map(const char*);
	void update_sequences(float time_delta);
	Character_Profile get_character_profile(const char*, bool absolute_path = false);
private:
	String get_full_filename(const String& filename);
	String get_canonical_path(const String& path);

	String m_asset_path;
	Table<String, Texture> m_textures;
	Table<String, Sound> m_sounds;
	// NOTE - this might not be future-proof
	Pool_Table<String, Sequence, 256> m_sequences;

	Sequence_Loader& m_sequence_loader;
};
