#pragma once
#include "utils/string.hpp"
#include "utils/table.hpp"
#include "utils/pool_table.hpp"
#include "sequence/sequence.hpp"
#include "map/map.hpp"
#include <raylib/raylib.h>

class Resource_Manager
{
public:
	Resource_Manager(const String& asset_path);

	Texture get_texture(const char* filename, bool absolute_path = false);
	Sequence& get_sequence(const char*, bool absolute_path = false);
	Map get_map(const char*);
private:
	String get_full_filename(const String& filename);
	String get_canonical_path(const String& path);

	String m_asset_path;
	Table<String, Texture> m_textures;
	// NOTE - this might not be future-proof
	Pool_Table<String, Sequence, 256> m_sequences;
};
