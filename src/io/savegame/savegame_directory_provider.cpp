#include "savegame_directory_provider.hpp"

#ifdef _WIN32
static_assert(false, "Not implemented for Windows yet. :(");
#else
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

Savegame_Directory_Provider::Savegame_Directory_Provider(const char* project_name)
{
#ifdef _WIN32
	static_assert(false, "Not implemented for Windows yet. :(");
#else
	m_path = getpwuid(getuid())->pw_dir;
	m_path.append("/.local/share/sage/savegame/");
	m_path.append(project_name);
#endif
}
