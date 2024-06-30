#include "mode_general.hpp"
#include "map/map.hpp"
#include "imgui.h"
#include "utils/filesystem.hpp"
#include "game/game_facade.hpp"

Dev_Tools_Mode_General::Dev_Tools_Mode_General(Game_Facade& facade, const String& project_root) :
	m_game_facade{facade}
{
	m_project_root = project_root;
}

void Dev_Tools_Mode_General::draw(const Map& map)
{
	ImGui::Begin("General", nullptr, ImGuiWindowFlags_NoCollapse);

	char requested_map[512] = {0};
	strcpy(requested_map, get_relative_path(map.get_path(), m_project_root).data());

	if (ImGui::InputText("Current map", requested_map, sizeof(requested_map), ImGuiInputTextFlags_EnterReturnsTrue)) {
		m_game_facade.set_current_map(requested_map);
	}

	ImGui::End();
}
