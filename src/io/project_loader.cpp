#include "project_loader.hpp"
#include "utils/file.hpp"
#include "cJSON.h"
#include "utils/log.hpp"

Project_Description load_project_description(String project_root)
{
	// Get file
	String project_file_path = project_root;
	project_file_path.append("/project.json");
	//SG_DEBUG("Loading project file \"%s\"", project_file_path.data());
	String file_content = read_file_to_str(project_file_path.data());
	
	// Parse json
	cJSON* json = cJSON_Parse(file_content.data());

	Project_Description description;
	description.name =
		cJSON_GetObjectItem(json, "name")->valuestring;
	description.start_sequence =
		cJSON_GetObjectItem(json, "sequence")->valuestring;

	cJSON_Delete(json);

	return description;
}
