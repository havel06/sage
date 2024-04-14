#include "file.hpp"
#include <stdio.h>
#include <assert.h>

String read_file_to_str(const char* filename)
{
	FILE* file = fopen(filename, "r");
	assert(file);

	String result;
	int c;
	while ((c = fgetc(file)) != EOF)
	{
		result.append((char)c);
	}

	fclose(file);

	return result;
}

