#pragma once
#include "../parameter.hpp"

class Text_Align_Parameter final : public Parameter
{
public:
	Game_UI::Text_Align value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
