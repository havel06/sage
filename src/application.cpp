#include "application.hpp"
#include "utils/log.hpp"
#include <raylib/raylib.h>

Application::Application()
{
	SetTraceLogLevel(LOG_ERROR);
	InitWindow(1280, 720, "Sage");
	SetTargetFPS(60);
	SetExitKey(0);
}

void Application::run(int argc, const char* argv[])
{
	if (argc < 2) {
		SG_ERROR("Command line argument missing.");
		return;
	}

	const char* project_path = argv[1];
	Game game(project_path);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		game.draw_frame(GetFrameTime());
		EndDrawing();
	}
}
