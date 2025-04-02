#include "sequence_list.hpp"
#include "graphics/editor_ui/factories/scroll.hpp"
#include "graphics/editor_ui/system.hpp"
#include "io/resource/sequence_manager.hpp"
#include "sequence_detail.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/fuzzy_match.hpp"
#include "graphics/editor_ui/factories/dummy.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/row.hpp"
#include "graphics/editor_ui/factories/button.hpp"
#include "graphics/editor_ui/factories/text.hpp"
#include "graphics/editor_ui/factories/divider.hpp"

Dev_Tools_Sequence_List::Dev_Tools_Sequence_List(Editor_UI::System& system, Sequence_Manager& seq_mgr,Dev_Tools_Sequence_Detail& detail,  const String& resource_root) :
	m_system{system},
	m_sequence_manager{seq_mgr},
	m_detail{detail},
	m_resource_root{resource_root}
{
}

void Dev_Tools_Sequence_List::set_searched_term(const String& searched_term)
{
	m_searched_term = searched_term;
	m_dirty = true;
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Sequence_List::build()
{
	m_dirty = false;
	
	using namespace Editor_UI::Factories;

	auto column = Column::make(Column::Padding::small);

	m_sequence_manager.for_each([&](const String& path, Sequence& seq){
		const String path_relative = get_relative_path(path, m_resource_root);
		const bool matches_search = fuzzy_match_string(m_searched_term, path_relative);

		if (matches_search) {
			column
				->add(build_item(path, seq))
				->add(Divider::make());
		}
	});

	return Scroll::make(column);
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Sequence_List::build_item(const String& path, Sequence&)
{
	using namespace Editor_UI::Factories;

	const String path_relative = get_relative_path(path, m_resource_root);

	return Row::make(true)
		->add(Text::make(m_system.get_font(), path_relative))
		->add(Button::make(
			[this, path=path](){
				m_detail.set_sequence(m_sequence_manager.get(path, true));
			})
			->with_icon(m_system.ICON_INFO)
		);
}

bool Dev_Tools_Sequence_List::is_dirty() const
{
	return m_dirty;
}
