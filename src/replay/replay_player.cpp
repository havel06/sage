#include "replay_player.hpp"
#include "replay/replay.hpp"
#include "utils/log.hpp"
#include "game/game.hpp"

Replay_Player::Replay_Player(const char* file)
{
	m_replay = Replay::load_from_file(file);
}

bool Replay_Player::should_exit() const
{
	return m_current_frame >= m_replay.frames.size();
}

void Replay_Player::run_frame(Game& game)
{
	if (should_exit())
		return;

	const Replay_Frame& frame = m_replay.frames[m_current_frame];
	game.draw_frame(frame.duration);
	m_current_frame++;
}

void Replay_Player::process(Input_Observer& observer)
{
	for (Input_Event event : m_replay.frames[m_current_frame].input_events)
		observer.handle_input_event(event);
}
