#pragma once

#include "string.hpp"

String remove_filename(const String& path);

String get_canonical_path(const String&);
String get_canonical_path(const char*);

bool directory_exists(const char*);
bool directory_exists(const String&);

bool file_exists(const char*);
bool file_exists(const String&);

void create_directory(const char*);
void create_directory(const String&);

void remove_directory(const String&);

String get_relative_path(const String& path, const String& base);
String resolve_relative_path(const String& relative_path, const String& base);

void create_directories_for_file(const String& path);
