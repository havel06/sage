#include "widget_factory.hpp"
#include "utils/move.hpp"

namespace Game_UI
{

Widget_Factory::Widget_Factory()
{
	register_parameter("name", m_name_parameter);
	register_parameter("fade_in", m_fade_in_parameter);
}

Own_Ptr<Widget> Widget_Factory::make_widget()
{
	Layout layout{layout_rows, layout_columns};

	for (auto& child : children) {
		layout.add(child->make_widget(), child->position_row, child->position_column);
	}

	return make_widget(move(layout), m_name_parameter.value, m_fade_in_parameter.value);
}

Array<Templated::Registered_Parameter> Widget_Factory::get_parameters_recursive()
{
	Array<Registered_Parameter> parameters;

	// Collect own parameters
	for_each_parameter([&](const String& name, Parameter& parameter) {
		parameters.push_back(Registered_Parameter{
			.name = name,
			.parameter = parameter
		});
	});

	// Collect child parameters
	for (auto& child : children) {
		Array<Registered_Parameter> child_parameters = child->get_parameters_recursive();
		for (Registered_Parameter& child_param : child_parameters) {
			parameters.push_back(child_param);
		}
	}

	return parameters;
}

}
