#pragma once
#include "../condition_factory.hpp"
#include "templating/parameter.hpp"

namespace Condition_Factories
{

class Player_Is_Looking final : public Condition_Factory
{
public:
	Player_Is_Looking();
	Own_Ptr<Condition> make_condition(Game_Facade&) override;
private:
	Direction_Parameter m_direction;
};

}
