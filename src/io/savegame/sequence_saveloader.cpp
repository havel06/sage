#include "sequence_saveloader.hpp"
#include "cJSON.h"
#include "utils/file.hpp"
#include "utils/filesystem.hpp"
#include "sequence/sequence.hpp"
#include "stdio.h"
#include "utils/log.hpp"

Sequence_Saveloader::Sequence_Saveloader(const String& project_path)
{
	m_project_path = project_path;
}

void Sequence_Saveloader::set_save_directory(const String& path)
{
	m_saved_sequences_dir = path;
	m_saved_sequences_dir.append("/sequences");

	create_directory(m_saved_sequences_dir);
}

void Sequence_Saveloader::save(const Sequence& sequence)
{
	String savefile_path = get_savefile_location(sequence.get_path());

	// Create JSON
	cJSON* json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "current_event", cJSON_CreateNumber(sequence.get_current_event_index()));
	
	// Write to file
	create_directories_for_file(savefile_path);
	FILE* f = fopen(savefile_path.data(), "w");
	assert(f);
	char* json_str = cJSON_Print(json);
	fputs(json_str, f);
	free(json_str);
	fclose(f);

	// Delete JSON
	cJSON_Delete(json);

	//SG_DEBUG("Saved state of sequence \"%s\".", savefile_path.data());
}

void Sequence_Saveloader::load(Sequence& sequence)
{
	String savefile_path = get_savefile_location(sequence.get_path());

	if (!file_exists(savefile_path))
		return;

	String file_contents = read_file_to_str(savefile_path.data());

	cJSON* json = cJSON_Parse(file_contents.data());
	sequence.set_current_event(cJSON_GetObjectItem(json, "current_event")->valueint);

	cJSON_Delete(json);

	//SG_DEBUG("Loaded state of sequence \"%s\".", savefile_path.data());
}

String Sequence_Saveloader::get_savefile_location(const String& sequence_path)
{
	String relative_path = get_relative_path(sequence_path, m_project_path);
	String save_file_path = m_saved_sequences_dir;
	save_file_path.append("/");
	save_file_path.append(relative_path);

	return save_file_path;
}
