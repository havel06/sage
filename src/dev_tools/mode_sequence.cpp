#include "mode_sequence.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widget.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/widgets/column.hpp"
#include "graphics/editor_ui/widgets/row.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widgets/scroll.hpp"
#include "graphics/editor_ui/widgets/divider.hpp"
#include "graphics/editor_ui/widgets/view_model_holder.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "graphics/editor_ui/widgets/input.hpp"
#include "io/resource/sequence_manager.hpp"
#include "raylib/raylib.h"
#include "sequence/sequence.hpp"
#include "utils/filesystem.hpp"
#include "utils/log.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/own_ptr.hpp"

Dev_Tools_Mode_Sequence::Dev_Tools_Mode_Sequence(Editor_UI::System& gui, Sequence_Manager& seq_manager, const String& resource_root_path) :
	m_gui{gui},
	m_resource_root{resource_root_path},
	m_detail{gui, resource_root_path},
	m_list{gui, seq_manager, m_detail, resource_root_path}
{
}


void Dev_Tools_Mode_Sequence::update()
{
	m_dirty = true;
}

bool Dev_Tools_Mode_Sequence::is_dirty() const
{
	return m_dirty;
}

Own_Ptr<Editor_UI::Widget> Dev_Tools_Mode_Sequence::build()
{
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();

	auto column = factory.make_column();

	column->add_child(create_search_bar());
	column->add_child(factory.make_view_model_holder(m_list));
	column->add_child(factory.make_view_model_holder(m_detail));

	m_dirty = false;
	return column;
}

Own_Ptr<Editor_UI::Widget> Dev_Tools_Mode_Sequence::create_search_bar()
{
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();
	auto input = factory.make_input("Search");

	input->on_edit = [this, input=input.get()](){
		m_list.rebuild(input->get_content());
	};

	return input;
}
