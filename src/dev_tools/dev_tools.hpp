#pragma once

#include "mode_general.hpp"
#include "mode_sequence.hpp"

enum class Dev_Tools_Mode
{
	general,
	entities,
	sequence
};

class Dev_Tools
{
public:
	// FIXME - use DI
	Dev_Tools(Game_Facade& facade, Sequence_Manager& seq_mgr, const String& project_root);
	~Dev_Tools();
	void draw(const Map&);
private:
	void draw_main_menu();

	Dev_Tools_Mode_General m_general;
	Dev_Tools_Mode_Sequence m_sequence;

	Dev_Tools_Mode m_mode = Dev_Tools_Mode::general;
};
