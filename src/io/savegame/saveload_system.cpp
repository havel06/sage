#include "saveload_system.hpp"
#include "io/resource/resource_system.hpp"
#include "game/game_logic.hpp"

Saveload_System::Saveload_System(
		User_Directory_Provider& user_dir_provider,
		Resource_System& resource_system,
		Game_Logic& logic,
		Camera_Controller& camera_controller,
		Scriptable_GUI& scriptable_gui,
		const String& project_dir) :
	m_logic_normal{logic.state_normal},
	m_game_saveloader{
		user_dir_provider,
		project_dir,
		camera_controller,
		resource_system.sequence_manager,
		resource_system.character_profile_manager,
		scriptable_gui,
		resource_system.texture_manager,
		logic
	},
	m_map_saveloader{
		resource_system.texture_manager,
		user_dir_provider,
		project_dir
	},
	m_sequence_saveloader{
		resource_system.sequence_manager,
		user_dir_provider,
		project_dir
	}
{
}

bool Saveload_System::can_load()
{
	return m_game_saveloader.can_load();
}

void Saveload_System::new_game()
{
	m_game_saveloader.new_game();
}

void Saveload_System::save_game()
{
	m_game_saveloader.save();
	m_map_saveloader.save(m_logic_normal.get_map(), m_logic_normal.get_map_filename());
	m_sequence_saveloader.save_all();
}

void Saveload_System::load_game()
{
	assert(can_load());
	m_game_saveloader.load();
	m_sequence_saveloader.reload_all();
	// NOTE - map loader does not have to be called,
	// since map state is automatically loaded when the current map is set by Game_Saveloader
}

void Saveload_System::load_map(Map& map, const String& filename)
{
	m_map_saveloader.load(map, filename);
}
