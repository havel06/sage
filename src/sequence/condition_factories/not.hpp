#pragma once
#include "../condition_factory.hpp"
#include "../event_parameter.hpp"

namespace Condition_Factories
{

class Not final : public Condition_Factory
{
public:
	Not();
	Own_Ptr<Condition> make_condition(Game_Facade&) override;
private:
	Condition_Event_Parameter m_condition;
};

}
