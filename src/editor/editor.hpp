#pragma once

#include "graphics/editor_ui/system.hpp"

class GUI_Loader;
class Item_Registry;

namespace Editor
{

class Editor
{
public:
	Editor(Editor_UI::System& gui_system, GUI_Loader&, Item_Registry&);
	void rebuild(); // Call when opened
	void draw(float dt);
	void input_char(char character);
	void input_key(int key);
private:
	GUI_Loader& m_gui_loader;
	Item_Registry& m_item_registry;

	Editor_UI::Context m_context;
};

};
