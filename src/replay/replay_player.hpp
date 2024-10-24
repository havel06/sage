#pragma once

#include "input/input_event_provider.hpp"
#include "replay.hpp"

class Replay_Player : public Input_Event_Provider
{
public:
	Replay_Player(const char* file);
	void process(Input_Observer&, float dt) override;
private:
	Replay m_replay;
	int m_next_event = 0;
	double m_current_time = 0;
};
