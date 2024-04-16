#pragma once

class Text_Box;

class Text_Box_Renderer
{
public:
	Text_Box_Renderer(const Text_Box&);
	void draw();
private:
	const Text_Box& m_text_box;
};
