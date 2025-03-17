#pragma once
#include "../parameter.hpp"

class Colour_Parameter final : public Parameter
{
public:
	Colour value = {0, 0, 0, 0};
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
