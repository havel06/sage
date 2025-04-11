#pragma once

#include "../widget.hpp"
#include "../theme.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/string.hpp"
#include "utils/colour.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "input_state.hpp"

// fwd
struct Font;

namespace Editor_UI::Widgets
{

class Input_Constraint
{
public:
	virtual bool is_valid(const String&) const = 0;
	virtual ~Input_Constraint() = default;
};

class Input_Constraint_None : public Input_Constraint
{
	bool is_valid(const String&) const override { return true; }
};

class Input_Constraint_Integer : public Input_Constraint
{
	bool is_valid(const String&) const override;
};

// Integer or decimal
class Input_Constraint_Number : public Input_Constraint
{
	bool is_valid(const String&) const override;
};

class Input : public Widget
{
public:
	Function_Wrapper<void()> on_edit = [](){};
	Function_Wrapper<void()> on_enter = [](){}; // Triggered when 'enter' key is pressed

	Input(const Font& font, const String& label, Input_State& state, Own_Ptr<Input_Constraint>&& constraint);

	bool is_valid() const;

	void draw(const Theme& theme, float dt) override;
	void draw_overlay(const Theme&, float) override {}
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
	void handle_character(char) override;
	void handle_key(int key) override;
private:
	Own_Ptr<Input_Constraint> m_constraint;
	Input_State& m_state;
	const Font& m_font;
	String m_label;
	Recti m_bounding_box; // Set by layout()
	float m_time_since_cursor_blink = 0;
};

}
