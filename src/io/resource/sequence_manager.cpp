#include "sequence_manager.hpp"
#include "../sequence_loader.hpp"

Sequence_Manager::Sequence_Manager(const String& resource_root_path, Sequence_Loader& loader) :
	Resource_Manager(resource_root_path),
	m_loader{loader}
{
}

Own_Ptr<Sequence> Sequence_Manager::load_resource(const String& filename)
{
	return make_own_ptr<Sequence>(m_loader.load(filename));
}

void Sequence_Manager::update(float time_delta)
{
	// FIXME
	(void)time_delta;
	assert(false);
	//m_sequences.for_each([&](const String&, Own_Ptr<Sequence>& seq){
	//	seq->update(time_delta);
	//});
}

void Sequence_Manager::save()
{
	// FIXME
	assert(false);
	//m_sequences.for_each([&](const String&, Own_Ptr<Sequence>& seq){
	//	m_sequence_saveloader.save(*seq);
	//});
}
