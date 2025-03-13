#pragma once
#include "../condition_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/position_parameter.hpp"

namespace Condition_Factories
{

class Is_Passable final : public Condition_Factory
{
public:
	Is_Passable();
	Own_Ptr<Condition> make_condition(Game_Facade&) override;
private:
	Position_Parameter m_position;
};

}
