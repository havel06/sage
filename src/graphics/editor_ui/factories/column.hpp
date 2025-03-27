#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"

// fwd
namespace Editor_UI::Widgets {
	enum class Column_Padding;
}

namespace Editor_UI::Factories
{

class Column final : public Widget_Factory2
{
public:
	enum class Padding {
		normal,
		small,
		none
	};

	static Column* make(Padding padding);
	Column(Padding padding);
	Column* add(Own_Ptr<Widget_Factory2>&& child); // Fluent API
	Own_Ptr<Widget> make_widget() override;
private:
	Widgets::Column_Padding convert_padding();

	Padding m_padding;
	Array<Own_Ptr<Widget_Factory2>> m_children;
};

};
