#include "mode_sequence.hpp"
#include "io/resource/sequence_manager.hpp"
#include "imgui.h"
#include "utils/filesystem.hpp"

Dev_Tools_Mode_Sequence::Dev_Tools_Mode_Sequence(Sequence_Manager& seq_manager, const String& resource_root_path) :
	m_sequence_manager{seq_manager}
{
	m_resource_root = resource_root_path;
}

void Dev_Tools_Mode_Sequence::draw()
{
	ImGui::Begin("Sequences");

	m_sequence_manager.for_each([&](Sequence& sequence){
		ImGui::Selectable(get_relative_path(sequence.get_path(), m_resource_root).data());
	});

	ImGui::End();
}
