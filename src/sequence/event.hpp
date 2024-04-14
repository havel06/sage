#pragma once

class Game_Facade;

class Event
{
public:
	virtual void update(Game_Facade&, float time_delta);
	virtual bool is_finished() const;
};
