#pragma once

#include "utils/string.hpp"

class Sequence;

// Saves progress of sequence
class Sequence_Saveloader
{
public:
	Sequence_Saveloader(const String& project_path);
	void set_save_directory(const String& path);

	void save(const Sequence&);
	void load(Sequence&);

private:
	String get_savefile_location(const String& sequence_path);

	String m_project_path;
	String m_saved_sequences_dir;

};
