#include "widget_factory.hpp"
#include "utils/move.hpp"

namespace Game_UI
{

Own_Ptr<Widget> Widget_Factory::make_widget()
{
	Layout layout{layout_rows, layout_columns};

	for (auto& child : children) {
		layout.add(child->make_widget(), child->position_row, child->position_column);
	}

	return make_widget(move(layout));
}

}
