#pragma once

#include "game/game.hpp"

class Application
{
public:
	void run(int argc, const char* argv[]);
private:
	void init_window();
};
