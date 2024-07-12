#pragma once

#include "../event.hpp"
#include "utils/string.hpp"
#include "combat/target_selection_type.hpp"

namespace Events
{


class Select_Target : public Event
{
public:
	Select_Target(Game_Facade&, Target_Selection_Type);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	Target_Selection_Type m_selection_type;
};

}
