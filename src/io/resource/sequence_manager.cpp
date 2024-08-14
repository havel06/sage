#include "sequence_manager.hpp"
#include "../sequence_loader.hpp"
#include "utils/own_ptr.hpp"

Sequence_Manager::Sequence_Manager(const String& resource_root_path, Sequence_Loader& loader, Sequence_Saveloader& saveloader) :
	Resource_Manager(resource_root_path),
	m_loader{loader},
	m_saveloader{saveloader}
{
}

Own_Ptr<Resource<Sequence>> Sequence_Manager::load_resource(const String& filename)
{
	Own_Ptr<Resource<Sequence>> seq = make_own_ptr<Resource<Sequence>>(filename, m_loader.load(filename));
	m_saveloader.load(seq->get(), filename);
	return seq;
}

void Sequence_Manager::update(float time_delta)
{
	for_each([&](const String&, Sequence& sequence){
		sequence.update(time_delta);
	});
}

void Sequence_Manager::save()
{
	for_each([&](const String& path, Sequence& sequence){
		m_saveloader.save(sequence, path);
	});
}

bool Sequence_Manager::can_unload_resource(const Sequence& sequence) const
{
	return !sequence.is_active();
}

void Sequence_Manager::unload_resource(Sequence& sequence, const String& path)
{
	m_saveloader.save(sequence, path);
}

void Sequence_Manager::reload_sequences()
{
	for_each([&](const String& path, Sequence& sequence){
		m_saveloader.load(sequence, path);
	});
}
