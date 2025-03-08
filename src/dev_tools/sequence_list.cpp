#include "sequence_list.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/widgets/column.hpp"
#include "graphics/editor_ui/widgets/row.hpp"
#include "graphics/editor_ui/widgets/divider.hpp"
#include "graphics/editor_ui/widgets/scroll.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "graphics/editor_ui/system.hpp"
#include "io/resource/sequence_manager.hpp"
#include "sequence_detail.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/fuzzy_match.hpp"

Dev_Tools_Sequence_List::Dev_Tools_Sequence_List(Editor_UI::System& system, Sequence_Manager& seq_mgr,Dev_Tools_Sequence_Detail& detail,  const String& resource_root) :
	m_system{system},
	m_sequence_manager{seq_mgr},
	m_detail{detail},
	m_resource_root{resource_root}
{
}

void Dev_Tools_Sequence_List::rebuild(const String& searched_term)
{
	m_searched_term = searched_term;
	m_dirty = true;
}

Own_Ptr<Editor_UI::Widget> Dev_Tools_Sequence_List::build()
{
	Editor_UI::Widget_Factory factory = m_system.get_widget_factory();
	Own_Ptr<Editor_UI::Widgets::Column> column = factory.make_column();
	column->padding = Editor_UI::Widgets::Column_Padding::small;

	m_sequence_manager.for_each([&](const String& path, Sequence&){
		const String path_relative = get_relative_path(path, m_resource_root);

		const bool matches_search = fuzzy_match_string(m_searched_term, path_relative);

		if (matches_search) {
			auto row = factory.make_row(true);
			row->add_child(factory.make_text(path_relative));
			row->add_child(
				factory.make_icon_button(
					m_system.ICON_INFO,
					[this, path=path](){
						m_detail.set_sequence(m_sequence_manager.get(path, true));
					}
				)
			);
			column->add_child(move(row));
			column->add_child(factory.make_divider());
		}
	});

	m_dirty = false;
	return factory.make_scroll(move(column));
}

bool Dev_Tools_Sequence_List::is_dirty() const
{
	return m_dirty;
}
