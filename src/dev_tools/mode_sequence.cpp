#include "mode_sequence.hpp"
#include "dev_tools/sequence_detail.hpp"
#include "dev_tools/sequence_list.hpp"
#include "graphics/editor_ui/factories/input_text.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/system.hpp"
#include "io/resource/sequence_manager.hpp"
#include "raylib/raylib.h"
#include "sequence/sequence.hpp"
#include "utils/filesystem.hpp"
#include "utils/log.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/own_ptr.hpp"
#include "graphics/editor_ui/factories/stateful.hpp"
#include "graphics/editor_ui/factories/column.hpp"

Dev_Tools_Mode_Sequence::Dev_Tools_Mode_Sequence(Sequence_Manager& seq_manager, const String& resource_root_path) :
	m_resource_root{resource_root_path},
	m_seq_manager{seq_manager}
{
}

bool Dev_Tools_Mode_Sequence::is_dirty() const
{
	return m_dirty;
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Mode_Sequence::build(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	m_dirty = false;

	auto detail = make_own_ptr<Dev_Tools_Sequence_Detail>(m_resource_root);
	auto list = make_own_ptr<Dev_Tools_Sequence_List>(m_seq_manager, *detail, m_resource_root);

	return Column::make(Column::Padding::normal)
		->add(create_search_bar(*list, theme))
		->add(Stateful::make(move(list)))
		->add(Stateful::make(move(detail)));
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Mode_Sequence::create_search_bar(Dev_Tools_Sequence_List& list, const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	auto callback = [&list](const String& text) {
		list.set_searched_term(text);
	};

	return Input_Text::make(m_input_state, theme.font, "Search")
		->on_edit(callback);
}
