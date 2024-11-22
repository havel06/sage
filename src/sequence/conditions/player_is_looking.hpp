#pragma once

#include "../condition.hpp"
#include "utils/direction.hpp"

namespace Conditions
{

class Player_Is_Looking : public Condition
{
public:
	Player_Is_Looking(Game_Facade& facade, Direction direction);
	bool is_satisfied() const override;
private:
	Direction m_direction;
};

}
