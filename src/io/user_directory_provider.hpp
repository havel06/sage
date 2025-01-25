#pragma once

#include "utils/string.hpp"

class User_Directory_Provider
{
public:
	User_Directory_Provider(const char* project_name);
	const String& get_savegame_path() const { return m_savegame_path; }
private:
	String m_savegame_path;
};
