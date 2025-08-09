#include "spacer.hpp"
#include "../widgets/spacer.hpp"

namespace Editor_UI::Factories
{


Spacer* Spacer::make(Vec2i size)
{
	return new Spacer(size);
}

Spacer::Spacer(Vec2i size)
{
	m_size = size;
}

Own_Ptr<Widget> Spacer::make_widget()
{
	return make_own_ptr<Widgets::Spacer>(m_size);
}


}
