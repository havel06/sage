#include "mode_entity.hpp"
#include "imgui.h"
#include "map/map.hpp"
#include "utils/log.hpp"

void Dev_Tools_Mode_Entity::draw(Map_Entities& entities)
{
	ImGui::Begin("Entities");
	for (int i = 0; i < entities.get_entity_count(); i++) {
		Entity& entity = entities.get_entity(i);
		const bool is_selected = m_selected_entity == &entity;
		if (ImGui::Selectable(entity.name.data(), is_selected)) {
			m_selected_entity = &entity;
		}
	}
	ImGui::End();

	if (m_selected_entity) {
		draw_entity_edit();
	}
}

void Dev_Tools_Mode_Entity::draw_entity_edit()
{
	ImGui::Begin("Edit entity");
	//ImGui::Text("Name: %s", m_selected_entity->name.data());

	//ImGui::InputScalarN("Position", ImGuiDataType_S32, &m_selected_entity->position, 2);
	ImGui::DragScalarN("Position", ImGuiDataType_S32, &m_selected_entity->position, 2, 0.2);

	float* move_speed = m_selected_entity->assigned_character.has_value() ?
		&m_selected_entity->assigned_character.value().get().move_speed : &m_selected_entity->move_speed;

	ImGui::DragFloat("Move speed", move_speed, 0.1, 0, 100, "%.2f");

	ImGui::End();
}
