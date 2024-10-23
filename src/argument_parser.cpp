#include "argument_parser.hpp"
#include "utils/log.hpp"
#include "utils/move.hpp"

Optional<Parsed_Arguments> Parsed_Arguments::parse(int argc, const char** argv)
{
	String directory;
	Array<String> flags;
	Table<String, String> options;

	if (argc < 2) {
		SG_ERROR("No command line arguments provided.");
		return {};
	}

	for (int i = 1; i < argc; i++) {
		String arg = argv[i];
		if (arg.length() >= 2 && arg[0] == '-' && arg[1] == '-') {
			String option_body = arg.substring(2, arg.length() - 2);

			// Scan the option body for '='
			bool is_option = false;
			for (int j = 1; j < option_body.length() - 1; j++) {
				if (option_body[j] == '=') {
					String option_name = option_body.substring(0, j);
					String option_value = option_body.substring(j + 1, option_body.length() - j - 1);
					options.insert(move(option_name), move(option_value));
					is_option = true;
					break;
				}
			}

			if (!is_option)
				flags.push_back(option_body);
		} else {
			if (directory.empty()) {
				directory = arg;
			} else {
				SG_WARNING("Positional argument \"%s\" ignored.", arg.data());
			}
		}
	}

	if (!flags.contains("help") && directory.empty()) {
		SG_ERROR("Missing project directory argument.");
	}

	return Parsed_Arguments {
		.flags = move(flags),
		.options = move(options),
		.directory = move(directory),
	};
}
