#pragma once

// FIXME - reduce includes
#include "dev_tools/dev_tools.hpp"
#include "game_logic.hpp"
#include "game_logic_state_combat.hpp"
#include "game_logic_state_normal.hpp"
#include "graphics/camera.hpp"
#include "graphics/camera_controller.hpp"
#include "graphics/combat_renderer/combat_renderer.hpp"
#include "graphics/debug_entity_renderer.hpp"
#include "graphics/inventory_renderer.hpp"
#include "graphics/main_menu_renderer.hpp"
#include "graphics/map_renderer.hpp"
#include "graphics/quest_log_renderer.hpp"
#include "graphics/scriptable_gui.hpp"
#include "graphics/text_box_renderer.hpp"
#include "input/input_event_provider.hpp"
#include "io/gui_loader.hpp"
#include "io/resource/resource_system.hpp"
#include "io/user_directory_provider.hpp"
#include "io/sequence/sequence_loader.hpp"
#include "io/savegame/saveload_system.hpp"
#include "map/map.hpp"
#include "music_player.hpp"
#include "replay/replay_recorder.hpp"
#include "sequence/sequence.hpp"
#include "combat/combat_controller.hpp"
#include "utils/optional.hpp"
#include "editor/editor.hpp"
#include "console.hpp"

struct Project_Description;

class Game : public Input_Observer
{
public:
	Game(const Project_Description&, bool display_fps, bool no_auto_save, const Optional<String>& record_filename, Input_Event_Provider& input_provider, bool headless);
	~Game();
	void draw_frame(float time_delta);
	bool should_exit() const;
private:
	void render(float dt);
	void handle_input_event(Input_Event) override;
	void handle_input_main_menu(Input_Event);
	void handle_input_normal(Input_Event);
	void handle_input_combat(Input_Event);
	void handle_input_inventory(Input_Event);
	void handle_input_quest_log(Input_Event);
	void do_player_movement();

	Input_Event_Provider& m_input;

	User_Directory_Provider m_user_dir_provider;
	// Resources
	Resource_System m_resource_system;
	// Logic
	Game_Logic m_logic;
	Music_Player m_music_player;
	Game_Facade m_game_facade;
	// Saveload
	Saveload_System m_saveloader;

	// Rendering
	Game_Camera m_camera;
	Map_Renderer m_map_renderer;
	Camera_Controller m_camera_controller;
	Text_Box_Renderer m_text_box_renderer;
	Inventory_Renderer m_inventory_renderer;
	Combat_Controller m_combat_controller;
	Combat_Renderer m_combat_renderer;
	Quest_Log_Renderer m_quest_log_renderer;
	Main_Menu_Renderer m_main_menu;
	Scriptable_GUI m_scriptable_gui;
	Debug_Entity_Renderer m_debug_entity_renderer;

	// Misc
	Replay_Recorder m_replay_recorder;
	Dev_Tools m_dev_tools;
	Editor::Editor m_editor;
	Console m_console;

	Vec2i m_initial_window_size;

	enum class Mode {
		game,
		dev_tools,
		editor
	};

	Mode m_mode = Mode::game;

	bool m_show_inventory = false;
	bool m_show_quest_log = false;
	bool m_show_console = false;
	bool m_display_fps = false;
	bool m_headless = false;
	Optional<String> m_record_filename;

	// Player controls
	bool m_go_up = false;
	bool m_go_down = false;
	bool m_go_left = false;
	bool m_go_right = false;
};
