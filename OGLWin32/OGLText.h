#pragma once

#include <string>
#include "Renderable.h"
#include "GLFont.h"

class OGLText : public Renderable
{
private:
	std::string m_text;
	Vec2f _position;
	std::string fontLoc;
	GLFont *m_font;

public:
	OGLText() :_position(Vec2f(0, 0)), m_text(""){};
	OGLText(Vec2f position, std::string text);
	OGLText(Vec2f position, std::string text, std::string fontLoc);

	~OGLText();
	void SetText(const char* text);
	void Render();

};