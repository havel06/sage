#include "item_edit_dialog.hpp"
#include "graphics/editor_ui/factories/button.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/relative_pane.hpp"
#include "graphics/editor_ui/factories/input_text.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "utils/log.hpp"
#include "item/item.hpp"


namespace Editor
{

Item_Edit_Dialog::Item_Edit_Dialog(Item& item)
	//m_item{item}
{
	m_input_state_id.set_content(item.id);
	m_input_state_name.set_content(item.name);

	if (item.assigned_sequence.has_value()) {
		m_input_state_sequence.set_content(item.assigned_sequence.value().get_path());
	}
}

Own_Ptr<Editor_UI::Widget_Factory> Item_Edit_Dialog::build(const Editor_UI::Theme& theme)
{
	m_dirty = false;
	
	using namespace Editor_UI::Factories;

	auto back_button_callback = [](){
		SG_DEBUG("FIXME - go back!");
	};

	return Relative_Pane::make(true,
		Column::make(Column::Padding::normal)
			->add(Button::make(back_button_callback)
				->with_text(theme.font, "back")
			)
			->add(Input_Text::make(m_input_state_id, theme.font, "Id"))
			->add(Input_Text::make(m_input_state_name, theme.font, "Name"))
			->add(Input_Text::make(m_input_state_sequence, theme.font, "Sequence"))
	);
}

}
