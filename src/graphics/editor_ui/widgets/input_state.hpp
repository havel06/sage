#pragma once

#include "utils/string.hpp"
#include "utils/array.hpp"
#include "utils/own_ptr.hpp"

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


class Input_State
{
public:
	bool active = false;

	Input_State(Own_Ptr<Input_Constraint>&&);

	const String& get_content() { return m_content; }
	int get_cursor_position() const { return m_cursor_position; }
	bool is_valid() const;
	void set_content(const String&);
	void insert_character(char character);
	const String& get_current_hint() const { return m_current_displayed_hint; }

	void delete_character();
	void delete_last_word();

	void move_cursor_left();
	void move_cursor_right();

	// Sets the possible strings for autocomplete.
	// The strings don't have to match the current content,
	// the widget will filter matching strings on its own.
	void set_hints(const Array<String>&);

	void fix_cursor_position();
	void choose_new_hint(); // Chooses new hint to be displayed
	void use_hint(); // Uses matching hints and adds to content
private:
	Own_Ptr<Input_Constraint> m_constraint;
	String m_label;
	String m_content;
	Array<String> m_hints; // Autocomplete hints
	String m_current_displayed_hint; // Current displayed autocomplete item
	int m_cursor_position = 0;

};

}
