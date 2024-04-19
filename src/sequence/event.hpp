#pragma once

class Game_Facade;

class Event
{
public:
	bool asynchronous = false;

	virtual ~Event() = default;
	virtual void update(float time_delta) = 0;
	virtual bool is_finished() const = 0;
	virtual void reset() = 0;

protected:
	Event(Game_Facade& facade) : m_game_facade{facade}
	{
	}

	Game_Facade& m_game_facade;
};
