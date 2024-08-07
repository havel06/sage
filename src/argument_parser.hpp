#pragma once

#include "utils/array.hpp"
#include "utils/string.hpp"
#include "utils/optional.hpp"

struct Parsed_Arguments
{
	Array<String> flags;
	String directory;

	static Optional<Parsed_Arguments> parse(int argc, const char** argv);
};