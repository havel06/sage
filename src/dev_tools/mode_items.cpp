#include "mode_items.hpp"
#include "item/item_registry.hpp"
#include "item/inventory.hpp"
#include "imgui.h"

Dev_Tools_Mode_Items::Dev_Tools_Mode_Items(const Item_Registry& reg, Inventory& inv) :
	m_item_registry{reg},
	m_inventory{inv}
{
}

void Dev_Tools_Mode_Items::draw()
{
	ImGui::Begin("Items", nullptr, ImGuiWindowFlags_NoCollapse);

	m_item_registry.for_each([this](const Item& item){
		const bool is_selected = m_selected_item == item.id;

		if (ImGui::Selectable(item.name.data(), is_selected)) {
			m_selected_item = item.id;
		}
	});

	if (ImGui::Button("Add to inventory")) {
		if (!m_selected_item.empty()) {
			m_inventory.add_item(m_selected_item, 1);
		}
	}

	ImGui::End();
}
