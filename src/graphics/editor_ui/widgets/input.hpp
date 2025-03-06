#pragma once

#include "../widget.hpp"
#include "../theme.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/string.hpp"
#include "utils/colour.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"

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
	bool active = false;
	Function_Wrapper<void()> on_edit = [](){};
	Function_Wrapper<void()> on_enter = [](){}; // Triggered when 'enter' key is pressed

	Input(const Font& font, const String& label, Own_Ptr<Input_Constraint>&&);
	const String& get_content() { return m_content; }
	bool is_valid() const;
	void set_content(const String&);

	// Sets the possible strings for autocomplete.
	// The strings don't have to match the current content,
	// the widget will filter matching strings on its own.
	void set_hints(const Array<String>&);

	void draw(const Theme& theme, float dt) override;
	void draw_overlay(const Theme&, float) override {}
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
	void handle_character(char) override;
	void handle_key(int key) override;
private:
	void fix_cursor_position();
	void choose_new_hint(); // Chooses new hint to be displayed
	void use_hint(); // Uses matching hints and adds to content

	const Font& m_font;
	Own_Ptr<Input_Constraint> m_constraint;
	String m_label;
	String m_content;
	Array<String> m_hints; // Autocomplete hints
	String m_current_displayed_hint; // Current displayed autocomplete item
	Recti m_bounding_box; // Set by layout()
	int m_cursor_position = 0;
	float m_time_since_cursor_blink = 0;
};

}
