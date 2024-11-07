#pragma once

#include "input/input_event_provider.hpp"
#include "replay.hpp"

class Game;

class Replay_Player : public Input_Event_Provider
{
public:
	Replay_Player(const char* file);
	bool should_exit() const;
	void run_frame(Game& game);
private:
	void process(Input_Observer&) override;

	Replay m_replay;
	int m_current_frame = 0;
};
