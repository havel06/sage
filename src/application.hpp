#pragma once

#include "game.hpp"

class Application
{
public:
	Application();
	void run();
private:
	Game m_game;
};
