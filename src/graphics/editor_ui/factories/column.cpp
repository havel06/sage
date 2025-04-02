#include "column.hpp"
#include "graphics/editor_ui/widgets/column.hpp"
#include "graphics/editor_ui/widgets/column_padding.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Column* Column::make(Padding padding)
{
	return new Column(padding);
}

Column::Column(Padding padding) :
	m_padding{padding}
{
}

Column* Column::add(Own_Ptr<Widget_Factory>&& child)
{
	m_children.push_back(move(child));
	return this;
}

Own_Ptr<Widget> Column::make_widget()
{
	auto column = make_own_ptr<Widgets::Column>();
	column->padding = convert_padding();

	for (auto& child : m_children) {
		column->add_child(child->make_widget());
	}

	return column;
}

Widgets::Column_Padding Column::convert_padding()
{
	switch (m_padding) {
		case Padding::normal:
			return Widgets::Column_Padding::normal;
		case Padding::small:
			return Widgets::Column_Padding::small;
		case Padding::none:
			return Widgets::Column_Padding::none;
	}
}

}
