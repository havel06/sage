#include "filesystem.hpp"
#include <filesystem>

String get_canonical_path(const String& str)
{
	return get_canonical_path(str.data());
}

String get_canonical_path(const char* str)
{
	return std::filesystem::canonical(str).c_str();
}
