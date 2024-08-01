#include "file.hpp"
#include <stdio.h>
#include <assert.h>
#include "log.hpp"

String read_file_to_str(const char* filename)
{
	FILE* file = fopen(filename, "r");

	if (!file) {
		SG_ERROR("Cannot open file %s\n", filename);
		return "";
	}

	String result;
	int c;
	while ((c = fgetc(file)) != EOF) {
		result.append((char)c);
	}

	fclose(file);

	return result;
}

