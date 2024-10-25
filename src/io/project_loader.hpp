#pragma once

#include "utils/string.hpp"
#include "utils/vec2.hpp"

struct GUI_Description
{
	String textbox_path;
	String inventory_path;
	String inventory_slot_path;
	String combat_menu_path;
	String combat_option_path;
	String quest_log_path;
	String quest_path;
	String main_menu_path;
	String main_menu_option_path;
};

struct Project_Description
{
	String path;
	String name;
	String start_sequence;
	String default_character;
	GUI_Description gui_description;
	Vec2i initial_window_size;
};

Project_Description load_project_description(String project_root);
