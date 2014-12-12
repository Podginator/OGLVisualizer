#pragma once

#include "OGLText.h"
#include "OGLWindow.h"
#include <gl/GLU.h>

void OGLText::SetText(const char* text)
{
    m_text = text;
}

void OGLText::Render()
{

    glPushMatrix();

    glTranslatef(_position.X(), _position.Y(), 0);
    glScalef(_size, _size, 1);
	
	if (_rot!=0)
		glMultMatrixf(MathHelper::Matrix4DtransformZ(_rot).data);


    glColor4f(_color.red, _color.green, _color.blue, _color.alpha);
    m_font->Begin();
    m_font->TextOut(m_text.c_str(), 0, 0, _position.Z());
    m_font->End();

    glPopMatrix();
}

OGLText::OGLText() :_position(Vec3f(0, 0, -1)), m_text(""), _fontLoc("calibri.glf"), _size(12.f), _color(Color("#ffffff"))
{
    m_font = new GLFont();
    m_font->Create(_fontLoc);
    _width = m_font->m_width * 0;
    _rot = 0.f;
};

OGLText::OGLText(const Vec2f& position, const Color& color, const std::string& text, float size) :_position(position.X(), position.Y(), -1.f), m_text(text), _fontLoc("sansserif.glf"), _color(color)
{
    m_font = new GLFont();
    m_font->Create(_fontLoc);
    //Approximation of size based on 12px 24px 22px
    _size = size * (1 - (1 / m_font->m_height));
    _width = m_font->m_width * text.size();
    _rot = 0.f;
}

OGLText::OGLText(const Vec3f& position, const Color& color, const std::string& text, float size) :_position(position), m_text(text), _fontLoc("sansserif.glf"), _color(color)
{
    m_font = new GLFont();
    m_font->Create(_fontLoc);
    //Approximation of size based on 12px 24px 22px
    _size = size * (1 - (1 / m_font->m_height));
    _width = m_font->m_width * text.size();
    _rot = 0.f;
}

OGLText::OGLText(Vec2f position, const Color& color, const std::string& text, const char* fontLoc, float size) :_position(position.X(), position.Y(), -1.f), m_text(text), _fontLoc(fontLoc), _color(color)
{
    m_font = new GLFont();
    m_font->Create(_fontLoc);
    //Create an approximation of how normal fontsizes work (Not 1:1, but close)
    _size = size * (1 - (1 / m_font->m_height));
    _width = _size * text.size();
    _rot = 0.f;
}


OGLText::OGLText(Vec3f position, const Color& color, const std::string& text, const char* fontLoc, float size) :_position(position), m_text(text), _fontLoc(fontLoc), _color(color)
{
    m_font = new GLFont();
    m_font->Create(_fontLoc);
    //Create an approximation of how normal fontsizes work (Not 1:1, but close)
    _size = size * (1 - (1 / m_font->m_height));
    _width = _size * text.size();
    _rot = 0.f;
}

OGLText::~OGLText()
{
    delete[] m_font;
}

void OGLText::Scale(float scale)
{
    float tempZ = _position.Z();
    _size *= scale;
    _position = _position * scale;
    _position.Z(tempZ);
}

void OGLText::Move(float x, float y)
{
    _position += Vec3f(x, y, 0);

}

void OGLText::MoveRel(float x, float y)
{
    _position += Vec3f(x, y, 0);
}

void OGLText::Rotate(float deg)
{
    _rot = deg;
}

void OGLText::CenterRotate(float deg)
{
    _rot = deg;
}