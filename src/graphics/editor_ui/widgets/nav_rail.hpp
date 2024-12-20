#pragma once

#include "../widget.hpp"
#include "../icon_resource.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "utils/string.hpp"

// fwd
struct Font;

namespace Editor_UI::Widgets
{

class Nav_Rail_Item
{
public:	
	Vec2i position = {0, 0};
	Nav_Rail_Item(const Font& font, const Icon_Resource& icon, const String& label);
	void draw();
	int get_width() const;
	void handle_mouse(Vec2i position, bool click);
private:
	const Font& m_font;
	const Icon_Resource& m_icon;
	String m_label;
	bool m_hover = false;
};

class Nav_Rail : public Widget
{
public:
	void add_item(Own_Ptr<Nav_Rail_Item>&&);
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
private:
	Recti m_bounding_box;
	Array<Own_Ptr<Nav_Rail_Item>> m_items;
};

}
