#include "sequence_list.hpp"
#include "graphics/editor_ui/factories/scroll.hpp"
#include "graphics/editor_ui/system.hpp"
#include "io/resource/sequence_manager.hpp"
#include "sequence/event.hpp"
#include "sequence_detail.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/fuzzy_match.hpp"
#include "graphics/editor_ui/factories/dummy.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/row.hpp"
#include "graphics/editor_ui/factories/button.hpp"
#include "graphics/editor_ui/factories/text.hpp"
#include "graphics/editor_ui/factories/divider.hpp"

Dev_Tools_Sequence_List::Dev_Tools_Sequence_List(Sequence_Manager& seq_mgr,Dev_Tools_Sequence_Detail& detail, const String& resource_root, const String& searched_term) :
	m_sequence_manager{seq_mgr},
	m_detail{detail},
	m_resource_root{resource_root},
	m_searched_term{searched_term}
{
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Sequence_List::build(const Editor_UI::Theme& theme)
{
	m_dirty = false;
	
	using namespace Editor_UI::Factories;

	auto column = Column::make(Column::Padding::small);

	m_sequence_manager.for_each([&](const String& path, Sequence& seq){
		const String path_relative = get_relative_path(path, m_resource_root);
		const bool matches_search = fuzzy_match_string(m_searched_term, path_relative);

		if (matches_search) {
			column
				->add(build_item(path, seq, theme))
				->add(Divider::make());
		}
	});

	return Scroll::make(m_scroll_state, column);
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Sequence_List::build_item(const String& path, Sequence&, const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	const String path_relative = get_relative_path(path, m_resource_root);

	return Row::make(true)
		->add(Text::make(theme.font, path_relative))
		->add(Button::make(
			[this, path=path](){
				m_detail.set_sequence(m_sequence_manager.get(path, true));
			})
			->with_icon(theme.ICON_INFO)
		);
}

bool Dev_Tools_Sequence_List::is_dirty() const
{
	return m_dirty;
}
