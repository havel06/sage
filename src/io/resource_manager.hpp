#pragma once
#include "utils/string.hpp"
#include "utils/table.hpp"
#include "sequence/sequence.hpp"
#include "map/map.hpp"
#include <raylib/raylib.h>

class Resource_Manager
{
public:
	Resource_Manager(const String& asset_path);

	Texture get_texture(const char* filename, bool absolute_path = false);
	Sequence& get_sequence(const char*);
	Map get_map(const char*);
private:
	String get_full_filename(const String& filename);

	String m_asset_path;
	Table<String, Texture> m_textures;
	Table<String, Sequence> m_sequences;
};
