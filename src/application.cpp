#include "application.hpp"
#include "argument_parser.hpp"
#include "io/project_loader.hpp"
#include "utils/log.hpp"
#include "utils/profiler.hpp"
#include <raylib/raylib.h>

Application::Application()
{
	SetTraceLogLevel(LOG_ERROR);
	InitWindow(1280, 720, "Sage");
	SetTargetFPS(60);
	SetExitKey(0);
	InitAudioDevice();
}

void Application::run(int argc, const char* argv[])
{
	Optional<Parsed_Arguments> arguments = Parsed_Arguments::parse(argc, argv);

	if (!arguments.has_value())
		return;

	const bool display_fps = arguments.value().flags.contains("fps");

	Project_Description description = load_project_description(arguments.value().directory);
	SG_INFO("Loaded project \"%s\"", description.name.data());
	SetWindowTitle(description.name.data());

	Game game = [&](){
		SG_PROFILE_SCOPE("Game initialisation");
		return Game{description, display_fps};
	}();

	while (!WindowShouldClose() && !game.should_exit()) {
		BeginDrawing();
		ClearBackground(BLACK);
		game.draw_frame(GetFrameTime());
		EndDrawing();
	}
}
