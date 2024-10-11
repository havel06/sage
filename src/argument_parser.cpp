#include "argument_parser.hpp"
#include "utils/log.hpp"

Optional<Parsed_Arguments> Parsed_Arguments::parse(int argc, const char** argv)
{
	String directory;
	Array<String> flags;

	if (argc < 2) {
		SG_ERROR("No command line arguments provided.");
		return {};
	}

	for (int i = 1; i < argc; i++) {
		String arg = argv[i];
		if (arg.length() >= 2 && arg[0] == '-' && arg[1] == '-') {
			flags.push_back(arg.substring(2, arg.length() - 2));
		} else {
			if (directory.empty()) {
				directory = arg;
			} else {
				SG_WARNING("Positional argument \"%s\" ignored.", arg.data());
			}
		}
	}

	if (directory.empty()) {
		SG_ERROR("Missing project directory argument.");
	}

	return Parsed_Arguments {
		.flags = flags,
		.directory = directory,
	};
}
