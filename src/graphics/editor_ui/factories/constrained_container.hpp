#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

class Constrained_Container final : public Widget_Factory2
{
public:
	static Own_Ptr<Constrained_Container> make(Vec2i max_size, Own_Ptr<Widget_Factory2>&& child);
	Constrained_Container(Vec2i max_size, Own_Ptr<Widget_Factory2>&& child);
	Own_Ptr<Widget> make_widget() override;
private:
	Vec2i m_max_size;
	Own_Ptr<Widget_Factory2> m_child;
};

};
