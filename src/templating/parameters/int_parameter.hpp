#pragma once
#include "../parameter.hpp"

class Int_Parameter final : public Parameter
{
public:
	int value = 0;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
