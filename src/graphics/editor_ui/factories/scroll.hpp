#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

class Scroll final : public Widget_Factory
{
public:
	static Scroll* make(Own_Ptr<Widget_Factory>&& child);
	Scroll(Own_Ptr<Widget_Factory>&& child);
	Own_Ptr<Widget> make_widget() override;
private:
	Own_Ptr<Widget_Factory> m_child;
};

};
