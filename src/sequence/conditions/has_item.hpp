#pragma once

#include "../condition.hpp"
#include "utils/string.hpp"

namespace Conditions
{

class Has_Item : public Condition
{
public:
	Has_Item(Game_Facade& facade, const String& id, int count);
	bool is_satisfied() const override;
private:
	String m_id;
	int m_count;
};

}
