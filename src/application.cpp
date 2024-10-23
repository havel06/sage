#include "application.hpp"
#include "argument_parser.hpp"
#include "io/project_loader.hpp"
#include "io/resource/resource_system.hpp"
#include "utils/log.hpp"
#include "utils/profiler.hpp"
#include <raylib/raylib.h>
#include <stdio.h>

void Application::run(int argc, const char* argv[])
{
	Optional<Parsed_Arguments> arguments = Parsed_Arguments::parse(argc, argv);

	if (!arguments.has_value())
		return;

	// Command line flags
	const bool cmd_help = arguments.value().flags.contains("help");

	if (cmd_help) {
		print_help();
		return;
	}

	init_window();

	const bool display_fps = arguments.value().flags.contains("fps");
	const bool no_auto_save = arguments.value().flags.contains("noautosave");

	Project_Description description = load_project_description(arguments.value().directory);
	SG_INFO("Loaded project \"%s\"", description.name.data());
	SetWindowTitle(description.name.data());

	Game game = [&](){
		SG_PROFILE_SCOPE("Game initialisation");
		return Game{description, display_fps, no_auto_save};
	}();

	while (!WindowShouldClose() && !game.should_exit()) {
		BeginDrawing();
		ClearBackground(BLACK);
		game.draw_frame(GetFrameTime());
		EndDrawing();
	}
}

void Application::init_window()
{
	SetTraceLogLevel(LOG_ERROR);
	InitWindow(1280, 720, "Sage");
	SetTargetFPS(60);
	SetExitKey(0);
	InitAudioDevice();
}

void Application::print_help()
{
	auto print_option = [](const char* name, const char* description) {
		printf("  --%s\n", name);
		printf("      %s\n", description);
	};

	puts("Usage:");
	puts("sage [options...] <project_path>");
	puts("");
	puts("Supported flags:");
	print_option("help", "Prints the available options.");
	print_option("fps", "Shows the current fps in the corner of the window.");
	print_option("nautosave", "Game does not automatically save when switching maps.");
	print_option("record=<file>", "Records the game into specified replay file.");
	print_option("replay=<file>", "Plays the specified replay file.");
}
