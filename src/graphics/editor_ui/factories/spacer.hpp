#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

class Spacer final : public Widget_Factory
{
public:
	static Spacer* make(Vec2i size);

	Own_Ptr<Widget> make_widget() override;
private:
	Spacer(Vec2i size);

	Vec2i m_size;
};

};
