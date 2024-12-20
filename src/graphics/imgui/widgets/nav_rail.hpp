#pragma once

#include "../widget.hpp"
#include "../icon_resource.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "utils/string.hpp"

namespace IMGUI::Widgets
{

class Nav_Rail_Item
{
public:	
	Nav_Rail_Item(const Icon_Resource& icon, const String& label);
	void draw(Vec2i position);
private:
	const Icon_Resource& m_icon;
	String m_label;
};

class Nav_Rail : public Widget
{
public:
	void add_item(Own_Ptr<Nav_Rail_Item>&&);
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
private:
	Vec2i m_position;
	Array<Own_Ptr<Nav_Rail_Item>> m_items;
};

}
