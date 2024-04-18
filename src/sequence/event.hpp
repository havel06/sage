#pragma once

class Game_Facade;

class Event
{
public:
	bool asynchronous = false;

	virtual ~Event() = default;
	virtual void update(Game_Facade&, float time_delta) = 0;
	virtual bool is_finished(Game_Facade&) const = 0;
	virtual void reset() = 0;
};
