#pragma once

#include "../widget.hpp"
#include "../icon_resource.hpp"
#include "utils/function_wrapper.hpp"
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
	using Callback = Function_Wrapper<void()>;

	Vec2i position = {0, 0};
	Nav_Rail_Item(const Font& font, const Icon_Resource& icon, const String& label);
	void layout(const Theme& theme);
	void draw(const Theme& theme, bool active);
	bool handle_mouse(Vec2i position, bool click); // Returns true on select
	int get_width() const { return m_width; }
private:
	int calculate_width(const Theme& theme) const;

	const Font& m_font;
	const Icon_Resource& m_icon;
	String m_label;
	bool m_hover = false;
	int m_width = 0;
};

class Nav_Rail : public Widget
{
public:
	Nav_Rail(Function_Wrapper<void(int)>&& callback);
	void add_item(Own_Ptr<Nav_Rail_Item>&&);
	void set_active_index(int index);
	// Widget overrides
	void handle_character(char) override {}
	void handle_key(int) override {}
	void draw(const Theme& theme, float dt) override;
	void draw_overlay(const Theme&, float) override {}
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
private:
	Function_Wrapper<void(int)> m_callback;
	Recti m_bounding_box;
	Array<Own_Ptr<Nav_Rail_Item>> m_items;
	int m_index_active = -1;
};

}
