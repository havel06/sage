#pragma once

#include "../event.hpp"
#include "utils/string.hpp"

namespace Events
{

class Set_Layer_Opacity : public Event
{
public:
	Set_Layer_Opacity(Game_Facade&, const String& layer_name, float opacity);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override {}
private:
	String m_layer_name;
	float m_opacity;
};

}
