#pragma once

#include "dev_tools/dev_tools.hpp"
#include "game_logic.hpp"
#include "game_logic_state_combat.hpp"
#include "game_logic_state_normal.hpp"
#include "graphics/camera.hpp"
#include "graphics/camera_controller.hpp"
#include "graphics/combat_renderer.hpp"
#include "graphics/debug_entity_renderer.hpp"
#include "graphics/inventory_renderer.hpp"
#include "graphics/main_menu_renderer.hpp"
#include "graphics/map_renderer.hpp"
#include "graphics/quest_log_renderer.hpp"
#include "graphics/scriptable_gui.hpp"
#include "graphics/text_box_renderer.hpp"
#include "input_event_provider.hpp"
#include "io/gui_loader.hpp"
#include "io/resource/resource_system.hpp"
#include "io/user_directory_provider.hpp"
#include "io/sequence/sequence_loader.hpp"
#include "io/savegame/map_saveloader.hpp"
#include "io/savegame/sequence_saveloader.hpp"
#include "io/savegame/game_saveloader.hpp"
#include "map/map.hpp"
#include "music_player.hpp"
#include "sequence/sequence.hpp"
#include "combat/combat_controller.hpp"

struct Project_Description;

class Game : public Input_Observer
{
public:
	Game(const Project_Description&, bool display_fps, bool no_auto_save);
	~Game();
	void draw_frame(float time_delta);
	bool should_exit() const;
private:
	void handle_input_event(Input_Event) override;
	void handle_input_main_menu(Input_Event);
	void handle_input_normal(Input_Event);
	void handle_input_combat(Input_Event);
	void handle_input_inventory(Input_Event);
	void handle_input_quest_log(Input_Event);
	void do_player_movement();

	Game_Facade m_game_facade;
	Sequence_Loader m_sequence_loader;
	Resource_System m_resource_system;
	User_Directory_Provider m_user_dir_provider;
	Map_Saveloader m_map_saveloader;
	Sequence_Saveloader m_sequence_saveloader;
	Game_Saveloader m_game_saveloader;
	Party m_party;
	Combat m_combat;
	Game_Logic_State_Normal m_logic_normal;
	Game_Logic_State_Combat m_logic_combat;
	Game_Logic m_logic;
	Music_Player m_music_player;
	GUI_Loader m_gui_loader;

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

	Dev_Tools m_dev_tools;

	bool m_dev_mode = false;
	bool m_show_inventory = false;
	bool m_show_quest_log = false;
	bool m_display_fps = false;

	// Player controls
	bool m_go_up = false;
	bool m_go_down = false;
	bool m_go_left = false;
	bool m_go_right = false;
};
