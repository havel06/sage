#include "version.hpp"

const char* get_engine_version()
{
	// MAJOR.MINOR[dev]
	// Dev is added for development versions between minor versions.
	// E.g. - 1.2dev is between 1.2 and 1.3

	return "0.1dev";
}
