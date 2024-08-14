#include "mode_sequence.hpp"
#include "io/resource/sequence_manager.hpp"
#include "imgui.h"
#include "utils/filesystem.hpp"
#include "utils/log.hpp"

Dev_Tools_Mode_Sequence::Dev_Tools_Mode_Sequence(Sequence_Manager& seq_manager, const String& resource_root_path) :
	m_sequence_manager{seq_manager}
{
	m_resource_root = resource_root_path;
}

void Dev_Tools_Mode_Sequence::draw()
{
	ImGui::Begin("Sequences");

	m_sequence_manager.for_each([&](const String& path, Sequence& sequence){
		const bool is_selected = m_selected_sequence.has_value() && &m_selected_sequence.value().get() == &sequence;
		const String relative_path = get_relative_path(path, m_resource_root);
		if (ImGui::Selectable(relative_path.data(), is_selected)) {
			m_selected_sequence = m_sequence_manager.get(path, true);
		}
	});

	ImGui::End();

	if (m_selected_sequence.has_value()) {
		draw_sequence_edit(m_selected_sequence.value().get());
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
