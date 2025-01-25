#pragma once
#include "../widget.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "column.hpp"
#include "utils/rect.hpp"
#include "card_type.hpp"

namespace Editor_UI::Widgets
{

class Card : public Widget
{
public:
	Card_Type type = Card_Type::filled;
	Column column; // Use this to get elements inside card

	Card(Card_Type type);
	void update() override;
	void draw(const Theme& theme, float dt) override;
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
	void handle_character(char) override;
	void handle_key(int) override;
	void handle_scroll(float amount) override;
private:
	Recti m_bounding_box;
};

}
