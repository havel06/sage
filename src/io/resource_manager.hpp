#pragma once
#include "utils/string.hpp"
#include "utils/table.hpp"
#include "utils/pool_table.hpp"
#include "sequence/sequence.hpp"
#include "map/map.hpp"
#include "character_profile.hpp"
#include "graphics/texture.hpp"
#include <raylib/raylib.h>

class Sequence_Loader;
class Sequence_Saveloader;

// FIXME - this class has too many responsibilities
class Resource_Manager
{
public:
	Resource_Manager(Sequence_Loader&, Sequence_Saveloader&, const String& asset_path);

	Sage_Texture get_texture(const char* filename, bool absolute_path = false);
	Sound get_sound(const char* filename);
	Sequence& get_sequence(const char*, bool absolute_path = false);
	Map get_map(const char*);
	Character_Profile get_character_profile(const char*, bool absolute_path = false);

	void update_sequences(float time_delta); // FIXME - this doesn't belong here
	void save_sequences(); // FIXME - does this belong here?
private:
	String get_full_filename(const String& filename);

	String m_asset_path;
	Table<String, Sage_Texture> m_textures;
	Table<String, Sound> m_sounds;
	Table<String, Own_Ptr<Sequence>> m_sequences;

	Sequence_Loader& m_sequence_loader;
	Sequence_Saveloader& m_sequence_saveloader;
};
