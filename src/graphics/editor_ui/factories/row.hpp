#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"

namespace Editor_UI::Factories
{

class Row final : public Widget_Factory2
{
public:
	Row(bool stretch);
	Row& add(Own_Ptr<Widget_Factory2>&& child);
	Own_Ptr<Widget> make_widget() override;
private:
	bool m_stretch;
	Array<Own_Ptr<Widget_Factory2>> m_children;
};

};
