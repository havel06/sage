#pragma once
#include "../parameter.hpp"

class Position_Parameter final : public Parameter
{
public:
	Position value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
