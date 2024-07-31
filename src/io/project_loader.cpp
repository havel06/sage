#include "project_loader.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"

static GUI_Description load_gui_description(const JSON::Object_View& json)
{
	GUI_Description description;

	description.textbox_path = json["textbox"].deprecated_as_string();
	description.inventory_path = json["inventory"].deprecated_as_string();
	description.inventory_slot_path = json["inventory_slot"].deprecated_as_string();
	description.combat_menu_path = json["combat_menu"].deprecated_as_string();
	description.combat_option_path = json["combat_option"].deprecated_as_string();
	description.quest_log_path = json["quest_log"].deprecated_as_string();
	description.quest_path = json["quest"].deprecated_as_string();
	description.main_menu_path = json["main_menu"].deprecated_as_string();
	description.main_menu_option_path = json["main_menu_option"].deprecated_as_string();

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
	description.name = view["name"].deprecated_as_string();
	description.start_sequence = view["sequence"].deprecated_as_string();
	description.default_character = view["default_character"].deprecated_as_string();

	if (view.has("gui"))
		description.gui_description = load_gui_description(view["gui"].as_object());

	return description;
}
