#pragma once

#include "../condition.hpp"

namespace Conditions
{

class Not : public Condition
{
public:
	Not(Game_Facade& facade, Condition_Ptr&& condition);
	bool is_satisfied() const override;
private:
	Condition_Ptr m_condition;
};

}
