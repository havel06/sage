#pragma once

#include "widget.hpp"

namespace Game_UI
{

// FIXME - adopt
// Abstract factory pattern
class Widget_Factory
{
public:
	virtual Own_Ptr<Widget> make_widget() = 0;
};

}
