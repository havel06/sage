#pragma once
#include "../parameter.hpp"

class Target_Selection_Type_Parameter final : public Parameter
{
public:
	Target_Selection_Type value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
