#pragma once

#include "utils/string.hpp"

struct Project_Description
{
	String name;
	String start_sequence;
};

Project_Description load_project_description(String project_root);
