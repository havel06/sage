#pragma once
#include "utils/string.hpp"
#include "utils/table.hpp"
#include "raylib/raylib.h"

class Resource_Manager
{
public:
	Resource_Manager(const String& asset_path);

	Texture get_texture(const char*);
private:
	String get_full_filename(const String& filename);

	String m_asset_path;
	Table<String, Texture> m_textures;
};
