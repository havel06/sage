#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

class Dialog final : public Widget_Factory
{
public:
	static Dialog* make(Vec2i size, Own_Ptr<Widget_Factory>&& child);
	Dialog(Vec2i size, Own_Ptr<Widget_Factory>&& child);
	Own_Ptr<Widget> make_widget() override;
private:
	Vec2i m_size;
	Own_Ptr<Widget_Factory> m_child;
};

};
