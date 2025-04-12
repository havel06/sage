#pragma once

#include "graphics/editor_ui/state.hpp"

namespace Editor
{

class Mode_GUI : public Editor_UI::State
{
public:
	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme&) override;
	bool is_dirty() const override { return false; }
private:
};

}
