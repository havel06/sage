#pragma once

#include "../event.hpp"
#include "graphics/ui/layout.hpp"

namespace Events
{

class Show_GUI : public Event
{
public:
	Show_GUI(Game_Facade&, UI::Widget_Ptr&& widget);
	void update(float time_delta) override;
	bool is_finished() const override;
	void reset() override;
private:
	UI::Widget_Ptr m_widget;
	bool m_activated = false;
};

}
