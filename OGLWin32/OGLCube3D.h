//Created for Graphics I and II
//Author: Minsi Chen
#pragma once

#include "Renderable.h"
#include "Listener.h"

class OGLCube : public Renderable
{
private:
    struct SimpleVertex
    {
        float position[3];
        float colour[3];
    };

private:
    SimpleVertex*	m_corners;
    unsigned int*	m_indices;

    void			InitUnitCube();

public:
    OGLCube();
    ~OGLCube();
    void CenterRotate(float deg){}
    void Rotate(float deg){}
    void Scale(float scale){}
    void Move(float x, float y){}
    void SetOpacity(float n){}



    void			Render();
};