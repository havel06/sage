#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"
#include "graphics/sprite.hpp"


namespace Editor_UI::Factories
{

class Image final : public Widget_Factory
{
public:
	static Image* make(const Sprite& sprite, Vec2i size);
	Image(const Sprite& sprite, Vec2i size);
	Own_Ptr<Widget> make_widget() override;
private:
	Sprite m_sprite;
	Vec2i m_size;
};

};
