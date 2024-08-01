#pragma once
#include "graphics/ui/layout.hpp"
#include "utils/string.hpp"
#include "io/resource/resource_handle.hpp"

class GUI_Loader;
class Game_Logic;
struct Font;

class Main_Menu_Renderer
{
public:
	Main_Menu_Renderer(Game_Logic&, Resource_Handle<Font> default_font);
	void load(GUI_Loader&, const String& menu_filename, const String& option_filename);
	void input_direction(Direction);
	void enter();
	void draw(float time_delta);
private:
	void use_fallback_widgets();
	void init_widgets(UI::Widget_Ptr&& main_widget, UI::Widget_Ptr& option_widget);

	Game_Logic& m_logic;
	Resource_Handle<Font> m_default_font;

	UI::Widget_Ptr m_widget;
};
