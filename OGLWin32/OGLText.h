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
    OGLText();
    OGLText(const Vec2f& position, const Color& color, const char* text, float size);
    OGLText(Vec2f position, const Color& color, const char*  text, const char* fontLoc, float size);

    ~OGLText(){}// delete m_font;
    void SetText(const char* text);
    void Render();

};