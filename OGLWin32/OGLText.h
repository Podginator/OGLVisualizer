#pragma once

#include <string>
#include "Renderable.h"
#include "GLFont.h"

class OGLText : public Renderable
{
private:
    Color _color;
    float _size;
    const char* m_text;
    Vec2f _position;
    const char* _fontLoc;
    GLFont *m_font;

public:
    OGLText() :_position(Vec2f(0, 0)), m_text(""), _fontLoc("calibri.glf"), _size(12.f), _color(Color("#ffffff"))
    {
        m_font = new GLFont();
        m_font->Create(_fontLoc);
    };
    OGLText(const Vec2f& position, const Color& color, const char* text, float size) :_position(position), m_text(text), _fontLoc("franklin_gothic.glf"), _color(color)
    {
        m_font = new GLFont();
        m_font->Create(_fontLoc);
        //Approximation of size based on 12px 24px 22px
        _size = size * (1 - (1 / m_font->m_height));
    }
    OGLText(Vec2f position, const Color& color, const char*  text, const char* fontLoc, float size) :_position(position), m_text(text), _fontLoc(fontLoc), _color(color)
    {
        m_font = new GLFont();
        m_font->Create(_fontLoc);
        //Create an approximation of how normal fontsizes work (Not 1:1, but close)
        _size = size * (1 - (1 / m_font->m_height));
    }

    ~OGLText(){ delete m_font; };
    void SetText(const char* text);
    void Render();

};