#include "resource_manager.hpp"
#include "raylib/raylib.h"
#include "sequence/sequence.hpp"
#include "io/sequence_loader.hpp"
#include "utils/log.hpp"
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
	SG_INFO("Loaded texture \"%s\"", filename);
	m_textures.insert(String{filename}, Texture{texture});
	return texture;
}

Sequence& Resource_Manager::get_sequence(const char* filename)
{
	Sequence* found = m_sequences.get(filename);
	if (found)
		return *found;

	String full_filename = get_full_filename(filename);
	Sequence_Loader loader;
	Sequence sequence = loader.load(full_filename);
	SG_INFO("Loaded sequence \"%s\"", filename);

	return m_sequences.insert(String{filename}, (Sequence&&)sequence);
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
