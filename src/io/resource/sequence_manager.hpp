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
	void save();
private:
	Own_Ptr<Sequence> load_resource(const String& filename) override;

	Sequence_Loader& m_loader;
	Sequence_Saveloader& m_saveloader;
};
