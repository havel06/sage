#pragma once

#include "utils/string.hpp"

struct Project_Description
{
	String path;
	String name;
	String start_sequence;
	String default_character;
};

Project_Description load_project_description(String project_root);
