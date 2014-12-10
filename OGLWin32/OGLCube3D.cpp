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
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(2, -2, 2, -2, -1, 1);
    glFrustum(1, -1, 1, -1, 1,100);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset The Current Modelview Matrix
    glLoadIdentity();

    //NEW//////////////////NEW//////////////////NEW//////////////////NEW/////////////
    static float rotqube = 0;
    //glScalef(512, 512, 1);
    glTranslatef(0.0f, 0.0f, -6.0f);	// Translate Into The Screen 7.0 Units
    //glRotatef(rotqube, 0.0f, 1.0f, 0.0f);	// Rotate The cube around the Y axis
    //glRotatef(rotqube, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);		// Draw The Cube Using quads
    glColor3f(0.0f, 1.0f, 0.0f);	// Color Blue
    glVertex3f(2.0f, 2.0f, -2.0f);	// Top Right Of The Quad (Top)
    glVertex3f(-2.0f, 2.0f, -2.0f);	// Top Left Of The Quad (Top)
    glVertex3f(-2.0f, 2.0f, 2.0f);	// Bottom Left Of The Quad (Top)
    glVertex3f(2.0f, 2.0f,  2.0f);	// Bottom Right Of The Quad (Top)
    glEnd();			// End Drawing The Cube

    rotqube += 0.9;
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

}