#pragma once

#include "widget.hpp"
#include "templating/templated.hpp"

namespace Game_UI
{

// FIXME - adopt
// Abstract factory pattern
class Widget_Factory : public Templated
{
public:
	Array<Size> layout_rows;
	Array<Size> layout_columns;
	int position_row;
	int position_column;
	Array<Own_Ptr<Widget_Factory>> children;
	Own_Ptr<Widget> make_widget();
private:
	virtual Own_Ptr<Widget> make_widget(Layout&&) = 0;
};

}
