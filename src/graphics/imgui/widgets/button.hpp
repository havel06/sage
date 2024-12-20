#pragma once

#include "utils/rect.hpp"
#include "../widget.hpp"
#include "utils/string.hpp"
#include "row.hpp"

// fwd
struct Font;
namespace IMGUI {
	class Icon_Resource;
}

namespace IMGUI::Widgets
{

class Button : public Widget
{
public:
	// Icon is optional
	Button(const Font& font, const String& label, const Icon_Resource* icon);

	void draw() override;
	Vec2i layout(Recti bounding_box) override;
private:
	const Font& m_font;
	String m_label;
	const Icon_Resource* m_icon = nullptr;
	Recti m_bounding_box;
};

}
