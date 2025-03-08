#include "filesystem.hpp"
#include <filesystem>
#include "utils/log.hpp"

String remove_filename(const String& path)
{
	const std::filesystem::path result = std::filesystem::path{path.data()}.remove_filename();
	const std::string result_str = std::string{result.native().begin(), result.native().end()};
	return String{result_str.c_str()};
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
	SG_DEBUG("Remove directory %s", path.data());
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

Array<String> read_directory_relative(const String& directory)
{
	Array<String> result;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(directory.data()))
		result.push_back(get_relative_path(entry.path().c_str(), directory));

	return result;
}
