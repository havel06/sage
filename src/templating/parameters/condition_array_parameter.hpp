#pragma once
#include "../parameter.hpp"

class Condition_Array_Parameter final : public Parameter
{
public:
	Array<Own_Ptr<Condition>> value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
