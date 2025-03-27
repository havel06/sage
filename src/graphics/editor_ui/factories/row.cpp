#include "row.hpp"
#include "graphics/editor_ui/widgets/row.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Row* Row::make(bool stretch)
{
	return new Row(stretch);
}

Row::Row(bool stretch) :
	m_stretch{stretch}
{
}

Row* Row::add(Own_Ptr<Widget_Factory2>&& child)
{
	m_children.push_back(move(child));
	return this;
}

Own_Ptr<Widget> Row::make_widget()
{
	auto row = make_own_ptr<Widgets::Row>();
	row->stretch = m_stretch;

	for (auto& child : m_children) {
		row->add_child(child->make_widget());
	}

	return row;
}

}
