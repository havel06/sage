#pragma once
#include "../condition_factory.hpp"
#include "../event_parameter.hpp"

namespace Condition_Factories
{

class Has_Item final : public Condition_Factory
{
public:
	Has_Item();
	Own_Ptr<Condition> make_condition(Game_Facade&) override;
private:
	String_Event_Parameter m_item;
	Int_Event_Parameter m_count;
};

}
