#include "resource_manager.hpp"
#include "character_profile.hpp"
#include "raylib/raylib.h"
#include "sequence/sequence.hpp"
#include "io/sequence_loader.hpp"
#include "io/tmj.hpp"
#include "utils/log.hpp"
#include "character_profile_loader.hpp"
#include "utils/filesystem.hpp"

Resource_Manager::Resource_Manager(Sequence_Loader& seq_loader, const String& asset_path) :
	m_sequence_loader{seq_loader}
{
	m_asset_path = asset_path;
}

Sage_Texture Resource_Manager::get_texture(const char* filename, bool absolute_path)
{
	String full_filename = absolute_path ? get_canonical_path(filename) : get_full_filename(filename);
	const Sage_Texture* found = m_textures.get(full_filename);
	if (found)
		return *found;

	Sage_Texture texture = {LoadTexture(full_filename.data()), full_filename};
	SG_INFO("Loaded texture \"%s\"", full_filename.data());
	//SG_DEBUG("%d", texture.id);
	m_textures.insert(String{full_filename}, Sage_Texture{texture});
	return texture;
}

Sound Resource_Manager::get_sound(const char* filename)
{
	String full_filename = get_full_filename(filename);

	const Sound* found = m_sounds.get(full_filename);
	if (found)
		return *found;

	Sound sound = LoadSound(full_filename.data());
	SG_INFO("Loaded sound \"%s\"", full_filename.data());
	m_sounds.insert(String{full_filename}, Sound{sound});
	return sound;
}

Sequence& Resource_Manager::get_sequence(const char* filename, bool absolute_path)
{
	String full_filename = absolute_path ? get_canonical_path(filename) : get_full_filename(filename);
	Own_Ptr<Sequence>* found = m_sequences.get(full_filename);
	if (found)
		return **found;

	//SG_DEBUG("Loading sequence \"%s\"", full_filename.data());
	Sequence sequence = m_sequence_loader.load(full_filename);
	SG_INFO("Loaded sequence \"%s\"", full_filename.data());

	return *m_sequences.insert(String{full_filename}, make_own_ptr<Sequence>((Sequence&&)sequence));
}

Map Resource_Manager::get_map(const char* filename)
{
	// TODO - caching?
	
	String full_filename = get_full_filename(filename);
	TMJ::Map_Loader loader(*this, full_filename);
	SG_INFO("Loaded map \"%s\"", full_filename.data());
	return loader.retrieve_map();
}

Character_Profile Resource_Manager::get_character_profile(const char* filename, bool absolute_path)
{
	// TODO - caching?
	String full_filename = absolute_path ? get_canonical_path(filename) : get_full_filename(filename);
	Character_Profile_Loader loader(*this);
	const auto profile = loader.load(full_filename.data());
	SG_INFO("Loaded character \"%s\"", full_filename.data());
	return profile;
}

String Resource_Manager::get_full_filename(const String& filename)
{
	String full_filename = m_asset_path;
	full_filename.append("/");
	full_filename.append(filename);

	return get_canonical_path(full_filename);
}

void Resource_Manager::update_sequences(float time_delta)
{
	m_sequences.for_each([&](const String&, Own_Ptr<Sequence>& seq){
		seq->update(time_delta);
	});
}
