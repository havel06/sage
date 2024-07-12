#include "select_target.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Select_Target::Select_Target(Game_Facade& facade, Target_Selection_Type selection_type) :
	Event{facade}
{
	m_selection_type = selection_type;
}

void Select_Target::update(float time_delta)
{
	// FIXME
	(void)time_delta;
}

bool Select_Target::is_finished() const
{
	// FIXME
	return true;
}

void Select_Target::reset()
{
	// FIXME
}

}
