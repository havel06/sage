#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

class Scroll final : public Widget_Factory2
{
public:
	static Scroll* make(Own_Ptr<Widget_Factory2>&& child);
	Scroll(Own_Ptr<Widget_Factory2>&& child);
	Own_Ptr<Widget> make_widget() override;
private:
	Own_Ptr<Widget_Factory2> m_child;
};

};
