#pragma once
#include "../parameter.hpp"

class String_Parameter final : public Parameter
{
public:
	String value = {};
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
