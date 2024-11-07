#pragma once

#include "game/game.hpp"

class Application
{
public:
	void run(int argc, const char* argv[]);
private:
	void init_window(Vec2i size, const char* title, int max_fps);
	void print_help();
};
