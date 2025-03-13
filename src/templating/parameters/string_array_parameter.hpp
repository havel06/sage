#pragma once
#include "../parameter.hpp"

class String_Array_Parameter final : public Parameter
{
public:
	Array<String> value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
