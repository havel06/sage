#include "map_saveloader.hpp"
#include "utils/filesystem.hpp"
#include "map/map.hpp"
#include "utils/log.hpp"
#include "stdio.h"

Map_Saveloader::Map_Saveloader(const String& project_dir)
{
	m_project_dir = project_dir;
}

void Map_Saveloader::set_save_directory(const String& path)
{
	// Create maps directory if needed
	m_saved_maps_dir = path;
	m_saved_maps_dir.append("/maps");

	if (!directory_exists(m_saved_maps_dir)) {
		create_directory(m_saved_maps_dir);
		SG_INFO("Created directory \"%s\".", m_saved_maps_dir.data());
	}
}

void Map_Saveloader::save(Map& map)
{
	assert(!m_project_dir.empty());
	assert(!m_saved_maps_dir.empty());

	if (map.get_path().empty()) {
		return;
	}

	String savefile = get_savefile_location(map.get_path());

	create_directories_for_file(savefile);
	FILE* f = fopen(savefile.data(), "w");
	assert(f);
	fputs("Hello world!", f);
	fclose(f);

	SG_INFO("Saved state of map \"%s\".", map.get_path().data());
}

void Map_Saveloader::load(Map& map)
{
	assert(!m_project_dir.empty());
	assert(!m_saved_maps_dir.empty());

	if (map.get_path().empty()) {
		return;
	}

	SG_INFO("Loaded state of map \"%s\".", map.get_path().data());
}

String Map_Saveloader::get_savefile_location(const String& map_path)
{
	String relative_path = get_relative_path(map_path, m_project_dir);
	String save_file_path = m_saved_maps_dir;
	save_file_path.append("/");
	save_file_path.append(relative_path);

	return save_file_path;
}
