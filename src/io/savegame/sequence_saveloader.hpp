#pragma once

#include "utils/string.hpp"

// fwd
class Sequence;
class Savegame_Directory_Provider;

// Saves progress of sequence
class Sequence_Saveloader
{
public:
	Sequence_Saveloader(Savegame_Directory_Provider&, const String& project_path);

	void save(const Sequence&, const String& path);
	void load(Sequence&, const String& path);
private:
	String get_savefile_location(const String& sequence_path);

	Savegame_Directory_Provider& m_savegame_dir_provider;

	String m_project_path;
	String m_saved_sequences_dir;

};
