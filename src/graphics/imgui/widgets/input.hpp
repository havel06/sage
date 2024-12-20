#pragma once

#include "../widget.hpp"
#include "utils/string.hpp"

namespace IMGUI::Widgets
{

class Input : public Widget
{
public:
	Input(const String& label, String& content, bool active);
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
private:
	String& m_content;
	String m_label;
	Recti m_bounding_box;
	bool m_active;
};

}
