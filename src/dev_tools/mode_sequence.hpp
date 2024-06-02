#pragma once
#include "utils/string.hpp"

// fwd
class Sequence_Manager;

// Sequence edit mode UI
class Dev_Tools_Mode_Sequence
{
public:
	Dev_Tools_Mode_Sequence(Sequence_Manager&, const String& resource_root_path);
	void draw();
private:
	Sequence_Manager& m_sequence_manager;
	String m_resource_root;
};
