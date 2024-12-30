#include "sequence_manager.hpp"
#include "../sequence/sequence_loader.hpp"
#include "utils/own_ptr.hpp"

Sequence_Manager::Sequence_Manager(const String& resource_root_path, Sequence_Loader& loader) :
	Resource_Manager(resource_root_path),
	m_loader{loader}
{
}

void Sequence_Manager::add_observer(Sequence_Manager_Observer& observer)
{
	m_observers.push_back(&observer);
}

Own_Ptr<Resource<Sequence>> Sequence_Manager::load_resource(const String& filename)
{
	Own_Ptr<Resource<Sequence>> seq = make_own_ptr<Resource<Sequence>>(filename, m_loader.load(filename));

	// Notify observers
	for (Sequence_Manager_Observer* observer : m_observers) {
		observer->on_load(filename, seq->get());
	}

	return seq;
}

void Sequence_Manager::update(float time_delta)
{
	for_each([&](const String&, Sequence& sequence){
		sequence.update(time_delta);
	});
}

bool Sequence_Manager::can_unload_resource(const Sequence& sequence) const
{
	return !sequence.is_active();
}

void Sequence_Manager::unload_resource(Sequence& sequence, const String& path)
{
	// Notify observers
	for (Sequence_Manager_Observer* observer : m_observers) {
		observer->on_load(path, sequence);
	}
}
