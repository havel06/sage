#include "activate_sequence.hpp"
#include "utils/own_ptr.hpp"
#include "io/resource/sequence_manager.hpp"
#include "../events/activate_sequence.hpp"

namespace Event_Factories {

Activate_Sequence::Activate_Sequence(Sequence_Manager& seq_mgr) :
	m_sequence_manager{seq_mgr}
{
	register_parameter("sequence", m_filename);
}

Own_Ptr<Event> Activate_Sequence::make_event(Game_Facade& facade)
{
	Resource_Handle<Sequence> sequence = m_sequence_manager.get(m_filename.value, false);
	return make_own_ptr<Events::Activate_Sequence>(facade, sequence);
}

}
