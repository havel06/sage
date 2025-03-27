#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/own_ptr.hpp"

// fwd
namespace Editor_UI {
	class Icon_Resource;
}

namespace Editor_UI::Factories
{

class Divider final : public Widget_Factory2
{
public:
	static Divider* make();
	Own_Ptr<Widget> make_widget() override;
private:
};

};
