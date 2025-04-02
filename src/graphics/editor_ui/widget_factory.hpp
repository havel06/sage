#pragma once

#include "widget.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI
{

class Widget_Factory
{
public:
	virtual ~Widget_Factory() = default;
	virtual Own_Ptr<Widget> make_widget() = 0;
};

}
