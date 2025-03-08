#pragma once
#include "utils/string.hpp"

String remove_filename(const String& path); // FIXME - move to filesystem.hpp?
String read_file_to_str(const char* filename);
