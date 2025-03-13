#pragma once
#include "../parameter.hpp"

class Battle_Units_Layout_Parameter final : public Parameter
{
public:
	Battle_Units_Layout value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
