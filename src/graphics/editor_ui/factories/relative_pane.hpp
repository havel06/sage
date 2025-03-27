#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

class Relative_Pane final : public Widget_Factory2
{
public:
	static Relative_Pane* make(bool padding, Own_Ptr<Widget_Factory2>&& child);
	Relative_Pane(bool padding, Own_Ptr<Widget_Factory2>&& child);
	Own_Ptr<Widget> make_widget() override;
private:
	bool m_padding;
	Own_Ptr<Widget_Factory2> m_child;
};

};
