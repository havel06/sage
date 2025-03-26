#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

class Progress_Bar final : public Widget_Factory2
{
public:
	Progress_Bar(float progress);
	Own_Ptr<Widget> make_widget() override;
private:
	float m_progress;
};

};
