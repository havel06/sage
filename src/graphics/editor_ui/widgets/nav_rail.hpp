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
	Nav_Rail_Item(const Font& font, const Icon_Resource& icon, const String& label, Callback&& callback);
	void layout(const Theme& theme);
	void draw(const Theme& theme, bool active);
	void handle_mouse(Vec2i position, bool click);
	int get_width() const { return m_width; }
private:
	int calculate_width(const Theme& theme) const;

	const Font& m_font;
	const Icon_Resource& m_icon;
	String m_label;
	Callback m_callback;
	bool m_hover = false;
	int m_width = 0;
};

class Nav_Rail : public Widget
{
public:
	// FIXME - refactor - don't let user construct Nav_Rail_Item directly?
	void add_item(Own_Ptr<Nav_Rail_Item>&&);
	void set_active_index(int index);
	void handle_character(char) override {}
	void handle_key(int) override {}
private:
	// Widget overrides
	void draw(const Theme& theme, float dt) override;
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;

	Recti m_bounding_box;
	Array<Own_Ptr<Nav_Rail_Item>> m_items;
	int m_index_active = -1;
};

}
