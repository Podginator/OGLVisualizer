#pragma once
#include "OGLShape.h"

void OGLShape::Rotate(float deg)
{
	Matrix<float> rotMat = MathHelper::Matrix2Dtransform(deg);

	for (int i = 0; i < _size; i++)
	{
		//Just rotates from center as origin. 
		vertexs[i] = rotMat * vertexs[i];
	}
}
void OGLShape::CenterRotate(float deg)
{
	Matrix<float> rotMat = MathHelper::Matrix2Dtransform(deg);
	for (int i = 0; i < _size; i++)
	{
		//Move it to the center.
		vertexs[i] -= _position;
		//Then rotate.
		vertexs[i] = rotMat * vertexs[i];
		//Then move back.
		vertexs[i] += _position;
	}	
}

void OGLShape::Render()
{

	//GLBegin basically just takes a Unsigned int Macro
	//So can pass it in as a variable
	glBegin(_renderType);
		RenderVertexs();
	glEnd();
}
void OGLShape::RenderVertexs()
{
	glColor3f(rgb.red, rgb.green, rgb.blue);
	for (int i = 0; i < _size; i++)
	{
		glVertex2f(vertexs[i].X(), vertexs[i].Y());
	}
	glPopMatrix();
}