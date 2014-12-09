//Created for Graphics I and II
//Author: Minsi Chen
#include "OGLCube3D.h"

#include <windows.h>
#include <gl\GL.h>
#include "MathHelper.h"

OGLCube::OGLCube()
{
    InitUnitCube();
}

OGLCube::~OGLCube()
{
    delete m_corners;
    delete m_indices;
}

void OGLCube::InitUnitCube()
{
    SimpleVertex corners[] =
    {
        { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.3f },// v0
        { 0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.4f }, // v1
        { 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f }, // v2
        { -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.6f }, // v3

        { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f }, // v4
        { 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.9f }, // v5
        { 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.8f}, // v6
        { -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.7f }, // v7
    };

    //Use triangles to define the faces, i.e. 2 triangles for one cube face
    unsigned int indices[] =
    {
        0, 1, 2, //+z face
        0, 2, 3,

        1, 5, 6, //+x face
        1, 6, 2,

        4, 7, 6, //-z face
        4, 6, 5,

        0, 3, 7, //-x face
        0, 7, 4,

        2, 6, 7, //+y face
        2, 7, 3,

        0, 4, 5, //-y face
        0, 5, 1
    };

    m_corners = new SimpleVertex[8];
    m_indices = new unsigned int[36];

    memcpy(m_corners, corners, sizeof(SimpleVertex)* 8);
    memcpy(m_indices, indices, sizeof(unsigned int)* 36);

}

void OGLCube::Render()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    static float a = 0;
    glRotatef(a, a, a, 1);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 36; i++)
    {

        SimpleVertex* vert = m_corners + m_indices[i];
        glColor3fv(vert->colour);
        glVertex3fv(vert->position);
    }
    a += 1;
    glEnd();

}