#pragma once

#include "widget.hpp"
#include "layout_description.hpp"
#include "templating/templated.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/string_parameter.hpp"
#include "templating/parameters/float_parameter.hpp"

namespace Game_UI
{

// FIXME - adopt
// Abstract factory pattern
class Widget_Factory : public Templated
{
public:
	int position_row;
	int position_column;
	Layout_Description layout_description;
	Array<Own_Ptr<Widget_Factory>> children;

	Widget_Factory();
	Own_Ptr<Widget> make_widget();
	Array<Registered_Parameter> get_parameters_recursive();
private:
	virtual Own_Ptr<Widget> make_widget(Layout&&, const String& name, float fade_in_out_time) = 0;
	String_Parameter m_name_parameter;
	Float_Parameter m_fade_in_parameter;
};

}
