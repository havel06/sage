#pragma once
#include "../parameter.hpp"
#include "graphics/game_ui/widget_factory.hpp"

class Widget_Parameter final : public Parameter
{
public:
	Own_Ptr<Game_UI::Widget_Factory> value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
