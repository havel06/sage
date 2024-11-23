#pragma once

#include "../condition.hpp"
#include "map/position.hpp"

namespace Conditions
{

class Is_Passable : public Condition
{
public:
	Is_Passable(Game_Facade& facade, const Position& position);
	bool is_satisfied() const override;
private:
	Position m_position;
};

}
