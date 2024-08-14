#pragma once

#include "io/savegame/sequence_saveloader.hpp"
#include "sequence/sequence.hpp"
#include "resource_manager.hpp"
#include "utils/concepts.hpp"

// fwd
class Sequence_Loader;

class Sequence_Manager : public Resource_Manager<Sequence>
{
public:
	Sequence_Manager(const String& resource_root_path, Sequence_Loader&, Sequence_Saveloader&);
	void update(float time_delta);

	// NOTE - saving sequences is handled by this class,
	// since it also loads the sequence state
	void save();
	void reload_sequences(); // Load savefiles for all loaded sequences

	// Callable must take two arguments, const String& (path) and Sequence&
	template<typename Fn>
	requires Concepts::Callable<Fn, const String&, Sequence&>
	void for_each(Fn c);
private:
	Own_Ptr<Resource<Sequence>> load_resource(const String& filename) override;
	void unload_resource(Sequence&, const String& path) override;
	bool can_unload_resource(const Sequence&) const override;

	Sequence_Loader& m_loader;
	Sequence_Saveloader& m_saveloader;
};


template<typename Fn>
requires Concepts::Callable<Fn, const String&, Sequence&>
void Sequence_Manager::for_each(Fn c)
{
	for_each_resource([&](Resource<Sequence>& res){
		c(res.get_path(), res.get());
	});
}
