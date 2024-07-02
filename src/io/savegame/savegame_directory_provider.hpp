#pragma once

#include "utils/string.hpp"

class Savegame_Directory_Provider
{
public:
	Savegame_Directory_Provider(const char* project_name);
	const String& get_path() const { return m_path; }
private:
	String m_path;
};
