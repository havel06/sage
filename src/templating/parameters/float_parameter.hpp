#pragma once
#include "../parameter.hpp"

class Float_Parameter final : public Parameter
{
public:
	float value = 0;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
