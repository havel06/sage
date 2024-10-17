#include "user_directory_provider.hpp"

#ifdef _WIN32
static_assert(false, "Not implemented for Windows yet. :(");
#else
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

User_Directory_Provider::User_Directory_Provider(const char* project_name)
{
	// FIXME - Windows support
#ifdef _WIN32
	static_assert(false, "Not implemented for Windows yet. :(");
#else
	String root_path = getpwuid(getuid())->pw_dir;
	root_path.append("/.local/share/sage");

	m_savegame_path = root_path;
	m_savegame_path.append("/savegame/");
	m_savegame_path.append(project_name);

	m_inifile_path = root_path;
	m_inifile_path.append("/imgui.ini");
#endif
}
