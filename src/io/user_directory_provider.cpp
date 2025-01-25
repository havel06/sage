#include "user_directory_provider.hpp"

#ifndef _WIN32
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#include <stdlib.h>

User_Directory_Provider::User_Directory_Provider(const char* project_name)
{
	// OS-specific
#ifdef _WIN32
	String appdata_folder = getenv("APPDATA");
	appdata_folder.append("/sage");

	m_savegame_path = appdata_folder;
#else
	String home_path = getpwuid(getuid())->pw_dir;
	home_path.append("/.local/share/sage");

	m_savegame_path = home_path;
#endif

	// OS-independent

	m_savegame_path.append("/savegame/");
	m_savegame_path.append(project_name);
}
