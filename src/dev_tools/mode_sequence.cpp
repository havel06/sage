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
		if (ImGui::Selectable(get_relative_path(sequence.get_path(), m_resource_root).data())) {
			m_selected_sequence = &sequence;
		}
	});

	ImGui::End();

	if (m_selected_sequence) {
		draw_sequence_edit(*m_selected_sequence);
	}
}

void Dev_Tools_Mode_Sequence::draw_sequence_edit(Sequence& sequence)
{
	ImGui::Begin("Edit sequence");

	ImGui::Text("Current event: %d", sequence.get_current_event_index());
	if (ImGui::Button("Reset sequence")) {
		sequence.reset();
	}

	ImGui::End();
}
