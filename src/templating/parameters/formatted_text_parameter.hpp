#pragma once
#include "../parameter.hpp"

class Formatted_Text_Parameter final : public Parameter
{
public:
	Game_UI::Formatted_Text value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
