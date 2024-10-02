#pragma once
#include "../condition_factory.hpp"
#include "../event_parameter.hpp"

namespace Condition_Factories
{

class Is_In_Combat final : public Condition_Factory
{
public:
	Is_In_Combat() = default;
	Own_Ptr<Condition> make_condition(Game_Facade&) override;
};

}
