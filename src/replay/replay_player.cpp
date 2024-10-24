#include "replay_player.hpp"
#include "utils/log.hpp"

Replay_Player::Replay_Player(const char* file)
{
	m_replay = Replay::load_from_file(file);
}

void Replay_Player::process(Input_Observer& observer, float dt)
{
	m_current_time += dt;

	while (true) {
		if (m_next_event >= m_replay.events.size())
			break;

		const Replay_Event& next_event = m_replay.events[m_next_event];
		if (next_event.event_time <= m_current_time) {
			SG_DEBUG("Event latency: %lf", m_current_time - next_event.event_time);
			observer.handle_input_event(next_event.input_event);
			m_next_event++;
		} else {
			break;
		}
	}
}
