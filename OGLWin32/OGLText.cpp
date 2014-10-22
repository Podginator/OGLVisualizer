#pragma once

#include "OGLText.h"


void OGLText::SetText(const char* text)
{
	m_text = text;
}


void OGLText::Render()
{
	glPushMatrix();

	glTranslatef(_position.X(), _position.Y(), 0);
	glScalef(_size, _size, 1);

	glColor3f(_color.red, _color.green, _color.blue);
	m_font->Begin();
	m_font->TextOut(m_text, 0, 0, 1);
	m_font->End();

	glPopMatrix();
}