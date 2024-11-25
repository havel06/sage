#include "set_layer_opacity.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Set_Layer_Opacity::Set_Layer_Opacity(Game_Facade& game_facade, const String& layer_name, float opacity) :
	Event{game_facade}
{
	m_layer_name = layer_name;
	m_opacity = opacity;
}

void Set_Layer_Opacity::update(float)
{
	m_game_facade.set_layer_opacity(m_layer_name, m_opacity);
}

bool Set_Layer_Opacity::is_finished() const
{
	return m_game_facade.get_layer_opacity(m_layer_name) == m_opacity;
}

}
