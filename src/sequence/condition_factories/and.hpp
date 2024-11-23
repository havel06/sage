#pragma once
#include "../condition_factory.hpp"
#include "../event_parameter.hpp"

namespace Condition_Factories
{

class And final : public Condition_Factory
{
public:
	And();
	Own_Ptr<Condition> make_condition(Game_Facade&) override;
private:
	Condition_Array_Event_Parameter m_conditions;
};

}
