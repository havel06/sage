#include "application.hpp"
#include "argument_parser.hpp"
#include "input/input_event_provider.hpp"
#include "input/user_input.hpp"
#include "io/project_loader.hpp"
#include "io/resource/resource_system.hpp"
#include "utils/log.hpp"
#include "utils/profiler.hpp"
#include "replay/replay_player.hpp"
#include "version.hpp"
#include <raylib/raylib.h>
#include <stdio.h>

void Application::run(int argc, const char* argv[])
{
	// FIXME - refactor this function

	Optional<Parsed_Arguments> arguments = Parsed_Arguments::parse(argc, argv);

	if (!arguments.has_value())
		return;

	// Command line flags
	const bool cmd_help = arguments.value().flags.contains("help");

	if (cmd_help) {
		print_help();
		return;
	}

	const bool display_fps = arguments.value().flags.contains("fps");
	const bool no_auto_save = arguments.value().flags.contains("noautosave");
	const bool headless = arguments.value().flags.contains("headless");

	int max_fps = 60;
	if (arguments.value().options.contains("maxfps")) {
		max_fps = atof(arguments.value().options.get("maxfps")->data());
	}

	if (arguments.value().options.contains("loglevel")) {
		const char* level_str = arguments.value().options.get("loglevel")->data();
		set_log_level(log_level_from_string(level_str, Log_Level::debug));
	}

	Optional<String> record_filename = arguments.value().options.get_opt("record");
	Optional<String> replay_filename = arguments.value().options.get_opt("replay");
	const bool do_replay = replay_filename.has_value();

	// Create input
	Own_Ptr<Replay_Player> replay_player;
	if (do_replay)
		replay_player = make_own_ptr<Replay_Player>(replay_filename.value().data());

	User_Input user_input;

	Input_Event_Provider& input = do_replay ? (Input_Event_Provider&)*replay_player : user_input;

	Project_Description description = load_project_description(arguments.value().directory);
	SG_INFO("Loaded project \"%s\"", description.name.data());

	if (strcmp(get_engine_version(), description.engine_version.data()) != 0) {
		SG_ERROR(
			"Required engine version (\"%s\") does not match current engine version (\"%s\").",
			description.engine_version.data(),
			get_engine_version()
		);
		return;
	}

	init_window(description.initial_window_size, description.name.data(), max_fps);

	Game game = [&](){
		SG_PROFILE_SCOPE("Game initialisation");
		return Game{description, display_fps, no_auto_save, record_filename, input, headless};
	}();

	while (!WindowShouldClose() && !game.should_exit()) {
		if (!headless) {
			BeginDrawing();
			ClearBackground(BLACK);
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		}

		if (do_replay) {
			if (replay_player->should_exit())
				break;
			replay_player->run_frame(game);
		} else {
			game.draw_frame(GetFrameTime());
		}

		if (!headless) {
			EndDrawing();
		}
	}
}

void Application::init_window(Vec2i size, const char* title, int max_fps)
{
	SetTraceLogLevel(LOG_ERROR);
	InitWindow(size.x, size.y, "Sage");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowMinSize(100, 100);
	SetWindowTitle(title);
	SetTargetFPS(max_fps);
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
	print_option("headless", "Game runs without any graphics.");
	print_option("record=<file>", "Records the game into specified replay file.");
	print_option("replay=<file>", "Plays the specified replay file.");
	print_option("maxfps=<number>", "Sets the maximum frames per second.");
}
