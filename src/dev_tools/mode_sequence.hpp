#pragma once
#include "io/resource/resource_handle.hpp"
#include "utils/string.hpp"
#include "utils/optional.hpp"

// fwd
class Sequence_Manager;
class Sequence;

// Sequence edit mode UI
class Dev_Tools_Mode_Sequence
{
public:
	Dev_Tools_Mode_Sequence(Sequence_Manager&, const String& resource_root_path);
	void draw();
private:
	void draw_sequence_edit(Sequence&);

	Sequence_Manager& m_sequence_manager;
	String m_resource_root;

	Optional<Resource_Handle<Sequence>> m_selected_sequence;
};
