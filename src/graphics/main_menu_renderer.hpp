#pragma once
#include "graphics/ui/layout.hpp"
#include "utils/string.hpp"

class GUI_Loader;
class Game_Logic;

class Main_Menu_Renderer
{
public:
	Main_Menu_Renderer(Game_Logic&);
	void load(GUI_Loader&, const String& project_root, const String& menu_filename, const String& option_filename);
	void input_direction(Direction);
	void enter();
	void draw(float time_delta);
private:
	Game_Logic& m_logic;

	UI::Widget_Ptr m_widget;
};
