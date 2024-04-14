#pragma once

class Game_Facade;

class Event
{
public:
	virtual ~Event() = default;
	virtual void update(Game_Facade&, float time_delta) = 0;
	virtual bool is_finished() const = 0;
};
