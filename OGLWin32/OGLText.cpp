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

OGLText::OGLText() :_position(Vec2f(0, 0)), m_text(""), _fontLoc("calibri.glf"), _size(12.f), _color(Color("#ffffff"))
{
    m_font = new GLFont();
    m_font->Create(_fontLoc);
};

OGLText::OGLText(const Vec2f& position, const Color& color, const char* text, float size) :_position(position), m_text(text), _fontLoc("sansserif.glf"), _color(color)
{
    m_font = new GLFont();
    m_font->Create(_fontLoc);
    //Approximation of size based on 12px 24px 22px
    _size = size * (1 - (1 / m_font->m_height));
}

OGLText::OGLText(Vec2f position, const Color& color, const char*  text, const char* fontLoc, float size) :_position(position), m_text(text), _fontLoc(fontLoc), _color(color)
{
    m_font = new GLFont();
    m_font->Create(_fontLoc);
    //Create an approximation of how normal fontsizes work (Not 1:1, but close)
    _size = size * (1 - (1 / m_font->m_height));
}