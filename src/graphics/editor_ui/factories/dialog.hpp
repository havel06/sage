#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

class Dialog final : public Widget_Factory2
{
public:
	static Dialog* make(Vec2i size, Own_Ptr<Widget_Factory2>&& child);
	Dialog(Vec2i size, Own_Ptr<Widget_Factory2>&& child);
	Own_Ptr<Widget> make_widget() override;
private:
	Vec2i m_size;
	Own_Ptr<Widget_Factory2> m_child;
};

};
