#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

class Progress_Bar final : public Widget_Factory
{
public:
	static Progress_Bar* make(float progress);
	Progress_Bar(float progress);
	Own_Ptr<Widget> make_widget() override;
private:
	float m_progress;
};

};
