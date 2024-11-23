#pragma once
#include "../condition_factory.hpp"
#include "../event_parameter.hpp"

namespace Condition_Factories
{

class Is_Passable final : public Condition_Factory
{
public:
	Is_Passable();
	Own_Ptr<Condition> make_condition(Game_Facade&) override;
private:
	Position_Event_Parameter m_position;
};

}
