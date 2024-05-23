#include "file.hpp"
#include <stdio.h>
#include <assert.h>
#include "log.hpp"

String remove_filename(const String& path)
{
	bool slash_found = false;
	int slash_position = 0;

	// Find the slash
	for (int i = 0; i < path.length(); i++) {
		if (path[i] == '/') {
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

String read_file_to_str(const char* filename)
{
	FILE* file = fopen(filename, "r");

	if (!file) {
		SG_ERROR("Cannot open file %s\n", filename);
		assert(false);
	}

	String result;
	int c;
	while ((c = fgetc(file)) != EOF) {
		result.append((char)c);
	}

	fclose(file);

	return result;
}

