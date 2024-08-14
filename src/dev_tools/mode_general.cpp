#include "mode_general.hpp"
#include "map/map.hpp"
#include "imgui.h"
#include "utils/filesystem.hpp"
#include "game/game_facade.hpp"
#include "game/game_logic.hpp"

Dev_Tools_Mode_General::Dev_Tools_Mode_General(Game_Facade& facade, Game_Logic& game_logic, const String& project_root) :
	m_game_facade{facade},
	m_game_logic{game_logic}
{
	m_project_root = project_root;
}

void Dev_Tools_Mode_General::draw(const String& map_filename)
{
	ImGui::Begin("General", nullptr, ImGuiWindowFlags_NoCollapse);

	char requested_map[512] = {0};
	if (!map_filename.empty())
		strcpy(requested_map, get_relative_path(map_filename, m_project_root).data());

	if (ImGui::InputText("Current map", requested_map, sizeof(requested_map), ImGuiInputTextFlags_EnterReturnsTrue)) {
		m_game_facade.set_current_map(requested_map);
	}

	if (ImGui::Button("Save game")) {
		m_game_facade.save_game();
	}

	if (ImGui::Button("Load last save")) {
		m_game_logic.continue_game(); // FIXME - is 'continue_game' a good name for the function?
	}

	ImGui::End();
}
