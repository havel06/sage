#pragma once

#include "layout.hpp"

namespace UI
{

// FIXME - consider refactoring
class Widget
{
public:
	float fade_in_out_time = 0.0;

	Widget(Layout&&);
	virtual ~Widget() = default;

	Widget_Ptr clone() const;
	void set_name(String&&);

	void show(bool value);
	bool is_showing() const; // Accounts for fade-in/out

	void draw(Recti parent_area, float parent_opacity, float time_delta);
	void draw_as_root(float time_delta);
	void process_click();

	// Should only be called once.
	// Returns true when focus was successful.
	bool focus_first();
	void lose_focus();
	Focus_Move_Result move_focus(Direction);
	Widget* get_focused_widget();

	void add_child(Widget_Ptr&&, int row, int column);
	void add_child(Widget_Ptr&&);
	void clear_children();
	Widget* get_widget_by_name(const String&);

protected:
	bool is_focused() const { return m_focused; }

private:
	bool m_should_show = true;
	float m_opacity = 0; // Goes from 0 to 1

	bool m_focused = false;
	String m_name = "";
	Layout m_layout;

	virtual void draw_impl(Recti parent_area, float opacity, float time_delta) = 0;
	virtual void process_click_impl() = 0;
	virtual Widget_Ptr clone_impl(Layout&&) const = 0;
	virtual bool is_focusable() const = 0;
};

}
