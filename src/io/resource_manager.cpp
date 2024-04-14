#include "resource_manager.hpp"
#include "raylib/raylib.h"
#include <cstdlib>

Resource_Manager::Resource_Manager(const String& asset_path)
{
	m_asset_path = asset_path;
}

Texture Resource_Manager::get_texture(const char* filename)
{
	const Texture* found = m_textures.get(filename);
	if (found)
		return *found;

	String full_filename = get_full_filename(filename);
	Texture texture = LoadTexture(full_filename.data());
	m_textures.insert(String{filename}, Texture{texture});
	return texture;

}

String Resource_Manager::get_full_filename(const String& filename)
{
	String full_filename = m_asset_path;
	full_filename.append("/");
	full_filename.append(filename);

	String real_path;
	real_path.reserve(512);
	realpath(full_filename.data(), real_path.data());

	return real_path;
}
