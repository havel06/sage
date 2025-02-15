#pragma once
#include "utils/own_ptr.hpp"

class Game_Facade;

class Condition
{
public:
	virtual ~Condition() = default;
	virtual bool is_satisfied() const = 0;

protected:
	Condition(Game_Facade& facade) : m_game_facade{facade}
	{
	}

	Game_Facade& m_game_facade;
};

using Condition_Ptr = Own_Ptr<Condition>;
