#include "dev_tools.hpp"
#include "imgui.h"
#include "utils/log.hpp"
#include "rlImGui.h"

Dev_Tools::Dev_Tools()
{
	rlImGuiSetup(true);
}

Dev_Tools::~Dev_Tools()
{
	rlImGuiShutdown();
}

void Dev_Tools::draw()
{
	rlImGuiBegin();

	ImGui::Begin("Test", nullptr, ImGuiWindowFlags_None);
	ImGui::Text("Hello world");
	ImGui::End();

	rlImGuiEnd();
}
