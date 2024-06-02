#include "dev_tools.hpp"
#include "imgui.h"
#include "utils/log.hpp"
#include "rlImGui.h"

Dev_Tools::Dev_Tools(Game_Facade& facade, const String& project_root) :
	m_general(facade, project_root)
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
			break;
		case Dev_Tools_Mode::objects:
			break;
	}

	rlImGuiEnd();
}

void Dev_Tools::draw_main_menu()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::MenuItem("General")) {
			m_mode = Dev_Tools_Mode::general;
		}
		if (ImGui::MenuItem("Objects")) {
			m_mode = Dev_Tools_Mode::objects;
		}
		if (ImGui::MenuItem("Sequence")) {
			m_mode = Dev_Tools_Mode::sequence;
		}
		ImGui::EndMainMenuBar();
	}
}
