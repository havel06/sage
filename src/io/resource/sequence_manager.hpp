#pragma once

#include "io/savegame/sequence_saveloader.hpp"
#include "sequence/sequence.hpp"
#include "resource_manager.hpp"

// fwd
class Sequence_Loader;

class Sequence_Manager : public Resource_Manager<Sequence>
{
public:
	Sequence_Manager(const String& resource_root_path, Sequence_Loader&, Sequence_Saveloader&);
	void update(float time_delta);
	void save(); // FIXME - This shouldn't be here

	// Callable must take one argument, Sequence&
	template<typename Callable>
	void for_each(Callable c);
private:
	Own_Ptr<Sequence> load_resource(const String& filename) override;

	Sequence_Loader& m_loader;
	Sequence_Saveloader& m_saveloader;
};


template<typename Callable>
void Sequence_Manager::for_each(Callable c)
{
	for_each_resource(c);
}
