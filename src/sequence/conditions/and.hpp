#pragma once

#include "../condition.hpp"
#include "utils/array.hpp"

namespace Conditions
{

class And : public Condition
{
public:
	And(Game_Facade& facade, Array<Condition_Ptr>&& conditions);
	bool is_satisfied() const override;
private:
	Array<Condition_Ptr> m_conditions;
};

}
