#pragma once

#include "mode_general.hpp"

enum class Dev_Tools_Mode
{
	general,
	objects,
	sequence
};

class Dev_Tools
{
public:
	Dev_Tools(Game_Facade& facade, const String& project_root);
	~Dev_Tools();
	void draw(const Map&);
private:
	void draw_main_menu();

	Dev_Tools_Mode_General m_general;

	Dev_Tools_Mode m_mode = Dev_Tools_Mode::general;
};
