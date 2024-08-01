#include "filesystem.hpp"
#include <filesystem>

String remove_filename(const String& path)
{
#ifdef _WIN32
	const char separator = '\\';
#else
	const char separator = '/';
#endif

	bool slash_found = false;
	int slash_position = 0;

	// Find the slash
	for (int i = 0; i < path.length(); i++) {
		if (path[i] == separator) {
			slash_found = true;
			slash_position = i;
		}
	}

	if (!slash_found)
		return path;

	// Reconstruct filename
	String result;
	for (int i = 0; i < slash_position; i++) {
		result.append(path[i]);
	}

	return result;
}


String get_canonical_path(const String& str)
{
	return get_canonical_path(str.data());
}

String get_canonical_path(const char* str)
{
	return std::filesystem::weakly_canonical(str).string().c_str();
}

bool directory_exists(const char* path)
{
	return std::filesystem::exists(path);
}

bool directory_exists(const String& path)
{
	return directory_exists(path.data());
}

bool file_exists(const char* path)
{
	return std::filesystem::exists(path);
}

bool file_exists(const String& path)
{
	return directory_exists(path.data());
}

void create_directory(const char* path)
{
	std::filesystem::create_directories(path);
}

void create_directory(const String& path)
{
	create_directory(path.data());
}

void remove_directory(const String& path)
{
	std::filesystem::remove_all(path.data());
}

String get_relative_path(const String& path, const String& base)
{
	return std::filesystem::relative(path.data(), base.data()).string().data();
}

String resolve_relative_path(const String& path, const String& base)
{
	String result = remove_filename(base);
	result.append('/');
	result.append(path);
	return get_canonical_path(result);
}

void create_directories_for_file(const String& path)
{
	std::filesystem::path directories = std::filesystem::path(path.data()).remove_filename();
	std::filesystem::create_directories(directories);
}
