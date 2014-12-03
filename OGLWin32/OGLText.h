#pragma once

#include <string>
#include "Renderable.h"
#include "GLFont.h"

class OGLText : public Renderable
{
private:
    Color _color;
    float _size;
    std::string m_text;
    Vec3f _position;
    const char* _fontLoc;
    GLFont *m_font;
    float _rot;
    float _x;

    void Copy(const OGLText& copy)
    {
        m_font = new GLFont;
        m_font->Create(copy._fontLoc);
        _position = copy._position;
        _fontLoc = copy._fontLoc;
        m_text = copy.m_text;
        _color = copy._color;
        _size = copy._size;
        _width = copy._width;
    }

public:
    OGLText();
    OGLText(const Vec2f& position, const Color& color, const std::string& text, float size);
    OGLText(const Vec3f& position, const Color& color, const std::string& text, float size);
    OGLText(Vec2f position, const Color& color, const std::string& text, const char* fontLoc, float size);
    OGLText(Vec3f position, const Color& color, const std::string& text, const char* fontLoc, float size);
    OGLText(const OGLText& copy)
    {
        Copy(copy);
    }

    OGLText& operator=(const OGLText& copy)
    {
        if (&copy != this)
        {
            m_font = new GLFont;
            m_font->Create(copy._fontLoc);
            _position = copy._position;
            _position.Z(copy._position.Z());
            m_text = copy.m_text;
            _color = copy._color;
            _size = copy._size;
            _width = copy._width;
            _fontLoc = copy._fontLoc;
        }

        return *this;
    }


    ~OGLText();

    float _width;
    void SetText(const char* text);
    void Render();
    void CenterRotate(float deg);
    void Rotate(float deg);
    void Scale(float scale);
    void Move(float x, float y);
    void MoveZ(float z)
    {
        _position += Vec3f(0, 0, z);
    }
    void SetOpacity(float n){ _color.alpha -= n; }
};