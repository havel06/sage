#pragma once

#include "io/savegame/sequence_saveloader.hpp"
#include "sequence/sequence.hpp"
#include "resource_manager.hpp"
#include "utils/concepts.hpp"
#include "sequence_manager_observer.hpp"

// fwd
class Sequence_Loader;

class Sequence_Manager : public Resource_Manager<Sequence>
{
public:
	Sequence_Manager(const String& resource_root_path, Sequence_Loader&);
	void update(float time_delta);
	void add_observer(Sequence_Manager_Observer&);

	// Callable must take two arguments, const String& (path) and Sequence&
	template<typename Fn>
	requires Concepts::Callable<Fn, const String&, Sequence&>
	void for_each(Fn c);
private:
	Own_Ptr<Resource<Sequence>> load_resource(const String& filename) override;
	void unload_resource(Sequence&, const String& path) override;
	bool can_unload_resource(const Sequence&) const override;

	Sequence_Loader& m_loader;
	Array<Sequence_Manager_Observer*> m_observers;
};


// IMPL
template<typename Fn>
requires Concepts::Callable<Fn, const String&, Sequence&>
void Sequence_Manager::for_each(Fn c)
{
	for_each_resource([&](Resource<Sequence>& res){
		c(res.get_path(), res.get());
	});
}
