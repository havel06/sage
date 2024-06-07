#include "application.hpp"
#include "io/project_loader.hpp"
#include "utils/log.hpp"
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
	if (argc < 2) {
		SG_ERROR("Command line argument missing.");
		return;
	}

	const char* project_path = argv[1];

	Project_Description description = load_project_description(String{project_path});
	SG_INFO("Loaded project \"%s\"", description.name.data());
	SetWindowTitle(description.name.data());

	Game game(description);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		game.draw_frame(GetFrameTime());
		EndDrawing();
	}
}
