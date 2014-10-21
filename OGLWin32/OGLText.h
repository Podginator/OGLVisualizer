#pragma once

#include <string>
#include "Renderable.h"

class OGLText : public Renderable
{
private:
	std::string m_text;
	Vec2f _position;
	std::string fontLoc;

public:
	OGLText();
	OGLText(Vec2f position,std::string text);
	OGLText(Vec2f position, std::string text, std::string fontLoc);

	~OGLText();
	void SetText(const char* text);
	void Render()

};