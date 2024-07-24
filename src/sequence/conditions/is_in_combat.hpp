#pragma once

#include "../condition.hpp"

namespace Conditions
{

class Is_In_Combat : public Condition
{
public:
	Is_In_Combat(Game_Facade& facade);
	bool is_satisfied() const override;
};

}
