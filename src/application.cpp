#include "application.hpp"
#include <raylib/raylib.h>

Application::Application()
{
	SetTraceLogLevel(LOG_ERROR);
	InitWindow(1280, 720, "Sage");
	SetTargetFPS(60);
	SetExitKey(0);
}

void Application::run()
{
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		m_game.draw_frame(GetFrameTime());
		EndDrawing();
	}
}
