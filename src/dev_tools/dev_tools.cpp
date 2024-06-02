#include "dev_tools.hpp"
#include "dev_tools/mode_sequence.hpp"
#include "imgui.h"
#include "utils/log.hpp"
#include "rlImGui.h"

Dev_Tools::Dev_Tools(Game_Facade& facade, Sequence_Manager& seq_mgr, const String& project_root) :
	m_general(facade, project_root),
	m_sequence(seq_mgr, project_root)
{
	rlImGuiSetup(true);
}

Dev_Tools::~Dev_Tools()
{
	rlImGuiShutdown();
}

void Dev_Tools::draw(const Map& map)
{
	rlImGuiBegin();

	draw_main_menu();

	switch (m_mode) {
		case Dev_Tools_Mode::general:
			m_general.draw(map);
			break;
		case Dev_Tools_Mode::sequence:
			m_sequence.draw();
			break;
		case Dev_Tools_Mode::entities:
			break;
	}

	rlImGuiEnd();
}

void Dev_Tools::draw_main_menu()
{
	/*
	ImGui::SetNextWindowPos({0, 0});
	ImGui::SetNextWindowSize({ImGui::GetMainViewport()->Size.x, 0});
	ImGui::Begin("Main menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::BeginTable("Main menu table", 3);
	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	if (ImGui::Selectable("General", m_mode == Dev_Tools_Mode::general)) {
		m_mode = Dev_Tools_Mode::general;
	}
	ImGui::TableNextColumn();
	if (ImGui::Selectable("Entities", m_mode == Dev_Tools_Mode::entitiesCallback c)) {
		m_mode = Dev_Tools_Mode::entities;
	}
	ImGui::TableNextColumn();
	if (ImGui::Selectable("Sequences", m_mode == Dev_Tools_Mode::sequence)) {
		m_mode = Dev_Tools_Mode::sequence;
	}
	ImGui::EndTable();
	ImGui::End();
	*/

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::MenuItem("General")) {
			m_mode = Dev_Tools_Mode::general;
		}
		if (ImGui::MenuItem("Entities")) {
			m_mode = Dev_Tools_Mode::entities;
		}
		if (ImGui::MenuItem("Sequence")) {
			m_mode = Dev_Tools_Mode::sequence;
		}
		ImGui::EndMainMenuBar();
	}
}
