#pragma once

#include "utils/string.hpp"
#include "utils/vec2.hpp"

class Resource_Manager;
class Game_Logic;

// FIXME - is this class really needed?
// Facade for sequence events to interface with the rest of the game.
class Game_Facade
{
public:
	Game_Facade(Resource_Manager&, Game_Logic&);
	void set_current_map(const String& filename);
	void teleport_player(Vec2i position);
	void display_text(String&& message);
	bool is_text_box_shown() const;
private:
	void spawn_player();

	Resource_Manager& m_res_manager;
	Game_Logic& m_logic;
};
