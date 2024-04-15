#include "resource_manager.hpp"
#include "raylib/raylib.h"
#include "sequence/sequence.hpp"
#include "io/sequence_loader.hpp"
#include "io/tmj.hpp"
#include "utils/log.hpp"
#include <cstdlib>

Resource_Manager::Resource_Manager(const String& asset_path)
{
	m_asset_path = asset_path;
}

Texture Resource_Manager::get_texture(const char* filename, bool absolute_path)
{
	String full_filename = absolute_path ? get_canonical_path(filename) : get_full_filename(filename);
	const Texture* found = m_textures.get(full_filename);
	if (found)
		return *found;

	Texture texture = LoadTexture(full_filename.data());
	SG_INFO("Loaded texture \"%s\"", full_filename.data());
	//SG_DEBUG("%d", texture.id);
	m_textures.insert(String{full_filename}, Texture{texture});
	return texture;
}

Sequence& Resource_Manager::get_sequence(const char* filename, bool absolute_path)
{
	String full_filename = absolute_path ? get_canonical_path(filename) : get_full_filename(filename);
	Sequence* found = m_sequences.get(full_filename);
	if (found)
		return *found;

	//SG_DEBUG("Loading sequence \"%s\"", full_filename.data());
	Sequence_Loader loader;
	Sequence sequence = loader.load(full_filename);
	SG_INFO("Loaded sequence \"%s\"", full_filename.data());

	return m_sequences.insert(String{full_filename}, (Sequence&&)sequence);
}

Map Resource_Manager::get_map(const char* filename)
{
	// TODO - caching?
	
	String full_filename = get_full_filename(filename);
	TMJ::Map_Loader loader(*this, full_filename);
	SG_INFO("Loaded map \"%s\"", full_filename.data());
	return loader.retrieve_map();
}

String Resource_Manager::get_full_filename(const String& filename)
{
	String full_filename = m_asset_path;
	full_filename.append("/");
	full_filename.append(filename);

	return get_canonical_path(full_filename);
}

String Resource_Manager::get_canonical_path(const String& path)
{
	char real_path[512];
	realpath(path.data(), real_path);

	return real_path;
}
