#pragma once
#include "../parameter.hpp"

class Direction_Parameter final : public Parameter
{
public:
	Direction value = {};
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
