#pragma once

namespace Editor_UI::Widgets
{

class Scroll_State
{
public:	
	int max_height = 300;

	void update_offset(int amount);
	int get_offset(int child_height, int bounding_box_height);
private:
	int m_offset = 0;
};

};
