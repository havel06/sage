#include "sequence_saveloader.hpp"
#include "../user_directory_provider.hpp"
#include "utils/file.hpp"
#include "utils/filesystem.hpp"
#include "sequence/sequence.hpp"
#include "stdio.h"
#include "utils/log.hpp"
#include "utils/json.hpp"
#include "io/resource/sequence_manager.hpp"

Sequence_Saveloader::Sequence_Saveloader(Sequence_Manager& manager, User_Directory_Provider& dir_provider, const String& project_path) :
	m_seq_manager{manager},
	m_savegame_dir_provider{dir_provider}
{
	m_project_path = project_path;
	manager.add_observer(*this);
}

void Sequence_Saveloader::save_sequence(const Sequence& sequence, const String& path)
{
	if (path.empty())
		return;

	String savefile_path = get_savefile_location(path);
	create_directories_for_file(savefile_path);

	JSON::Object json;
	json.add("current_event", JSON::Value{sequence.get_current_event_index()});
	json.write_to_file(savefile_path.data());

	//SG_DEBUG("Saved state of sequence \"%s\".", savefile_path.data());
}

void Sequence_Saveloader::load_sequence(Sequence& sequence, const String& path)
{
	if (path.empty())
		return;

	String savefile_path = get_savefile_location(path);

	if (!file_exists(savefile_path))
		return;

	JSON::Object json = JSON::Object::from_file(savefile_path.data());
	JSON::Object_View view = json.get_view();
	sequence.set_current_event(view["current_event"].as_int(0));

	//SG_DEBUG("Loaded state of sequence \"%s\".", savefile_path.data());
}

String Sequence_Saveloader::get_savefile_location(const String& sequence_path)
{
	String path_relative_to_project = get_relative_path(sequence_path, m_project_path);

	String save_file_path = m_savegame_dir_provider.get_savegame_path();
	save_file_path.append("/sequences/");
	save_file_path.append(path_relative_to_project);

	return save_file_path;
}

void Sequence_Saveloader::on_load(const String& filename, Sequence& sequence)
{
	load_sequence(sequence, filename);
}

void Sequence_Saveloader::on_unload(const String& filename, Sequence& sequence)
{
	save_sequence(sequence, filename);
}

void Sequence_Saveloader::save_all()
{
	m_seq_manager.for_each([&](const String& path, Sequence& sequence){
		save_sequence(sequence, path);
	});
}

void Sequence_Saveloader::reload_all()
{
	m_seq_manager.for_each([&](const String& path, Sequence& sequence){
		load_sequence(sequence, path);
	});
}
