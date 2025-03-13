#pragma once
#include "../parameter.hpp"

class Sprite_Parameter final : public Parameter
{
public:
	Animated_Sprite value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};
