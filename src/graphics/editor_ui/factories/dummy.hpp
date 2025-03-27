#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/own_ptr.hpp"

// fwd
namespace Editor_UI {
	class Icon_Resource;
}

namespace Editor_UI::Factories
{

class Dummy final : public Widget_Factory2
{
public:
	static Dummy* make();
	Own_Ptr<Widget> make_widget() override;
private:
};

};
