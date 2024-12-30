#pragma once

#include "utils/string.hpp"
#include "io/resource/sequence_manager_observer.hpp"

// fwd
class Sequence;
class User_Directory_Provider;
class Sequence_Manager;

// Saves and loads progress of sequence
class Sequence_Saveloader : public Sequence_Manager_Observer
{
public:
	Sequence_Saveloader(Sequence_Manager&, User_Directory_Provider&, const String& project_path);
	Sequence_Saveloader(Sequence_Saveloader&&) = delete;
	Sequence_Saveloader(const Sequence_Saveloader&) = delete;

	void save_all();
	void reload_all();
private:
	// observer overrides
	void on_load(const String& filename, Sequence&) override;
	void on_unload(const String& filename, Sequence&) override;
	

	void save_sequence(const Sequence&, const String& path);
	void load_sequence(Sequence&, const String& path);

	String get_savefile_location(const String& sequence_path);

	Sequence_Manager& m_seq_manager;	
	User_Directory_Provider& m_savegame_dir_provider;

	String m_project_path;
	String m_saved_sequences_dir;

};
