#include "project_loader.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"

Project_Description load_project_description(String project_root)
{
	// Get file
	String project_file_path = project_root;
	project_file_path.append("/project.json");
	JSON::Object json = JSON::Object::from_file(project_file_path.data());
	JSON::Object_View view = json.get_view();

	Project_Description description;
	description.path = project_root;
	description.name = view["name"].as_string();
	description.start_sequence = view["sequence"].as_string();
	description.default_character = view["default_character"].as_string();

	return description;
}
