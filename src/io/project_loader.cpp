#include "project_loader.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"

static GUI_Description load_gui_description(const JSON::Object_View& json)
{
	GUI_Description description;

	description.textbox_path = json["textbox"].as_string("");
	description.inventory_path = json["inventory"].as_string("");
	description.inventory_slot_path = json["inventory_slot"].as_string("");
	description.combat_menu_path = json["combat_menu"].as_string("");
	description.combat_option_path = json["combat_option"].as_string("");
	description.quest_log_path = json["quest_log"].as_string("");
	description.quest_path = json["quest"].as_string("");
	description.main_menu_path = json["main_menu"].as_string("");
	description.main_menu_option_path = json["main_menu_option"].as_string("");

	return description;
}

Project_Description load_project_description(String project_root)
{
	// Get file
	String project_file_path = project_root;
	project_file_path.append("/project.json");
	JSON::Object json = JSON::Object::from_file(project_file_path.data());
	JSON::Object_View view = json.get_view();

	Project_Description description;
	description.path = project_root;

	description.name = view["name"].as_string("Project");
	description.start_sequence = view["sequence"].as_string("");
	description.initial_window_size.x = view["window_size_x"].as_int(1280);
	description.initial_window_size.y = view["window_size_y"].as_int(720);
	description.engine_version = view["version"].as_string("");

	if (description.start_sequence.empty()) {
		SG_ERROR("Initial sequence has not been set.");
		return description;
	}

	description.default_character = view["default_character"].as_string("");

	if (description.default_character.empty()) {
		SG_ERROR("Default character has not been set.");
		return description;
	}

	if (description.engine_version.empty()) {
		SG_ERROR("Engine version has not been set.");
		return description;
	}

	description.gui_description = load_gui_description(view["gui"].as_object());

	return description;
}
