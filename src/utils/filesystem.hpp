#pragma once

#include "string.hpp"

String get_canonical_path(const String&);
String get_canonical_path(const char*);

bool directory_exists(const char*);
bool directory_exists(const String&);

void create_directory(const char*);
void create_directory(const String&);

String get_relative_path(const String& path, const String& base);

void create_directories_for_file(const String& path);
