#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"

namespace Editor_UI::Factories
{

class Row final : public Widget_Factory
{
public:
	static Row* make(bool stretch);
	Row(bool stretch);
	Row* add(Own_Ptr<Widget_Factory>&& child);
	Own_Ptr<Widget> make_widget() override;
private:
	bool m_stretch;
	Array<Own_Ptr<Widget_Factory>> m_children;
};

};
