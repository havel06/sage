#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

// A widget that limits the maximum size of its child
class Constrained_Container final : public Widget_Factory
{
public:
	static Constrained_Container* make(Vec2i max_size, Own_Ptr<Widget_Factory>&& child);
	Constrained_Container(Vec2i max_size, Own_Ptr<Widget_Factory>&& child);
	Own_Ptr<Widget> make_widget() override;
private:
	Vec2i m_max_size;
	Own_Ptr<Widget_Factory> m_child;
};

};
