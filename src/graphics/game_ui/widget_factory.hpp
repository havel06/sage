#pragma once

#include "widget.hpp"
#include "templating/templated.hpp"

namespace Game_UI
{

// FIXME - adopt
// FIXME - add some sort of a 'layout factory' to make an editable layout
// Abstract factory pattern
class Widget_Factory : public Templated
{
public:
	virtual Own_Ptr<Widget> make_widget() = 0;
};

}
