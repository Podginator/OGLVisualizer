#pragma once
#include "OGLShape.h"


void OGLShape::Rotate(float deg)
{
	Matrix<float> rotMat = MathHelper<float>::Matrix2Dtransform(deg);

	for (int i = 0; i < _size; i++)
	{
		vertexs[i] = rotMat * vertexs[i];
	}
}
void OGLShape::CenterRotate(float deg)
{
	Matrix<float> rotMat = MathHelper<float>::Matrix2Dtransform(deg);
	for (int i = 0; i < _size; i++)
	{
		vertexs[i] -= _position;
		vertexs[i] = rotMat * vertexs[i];
		vertexs[i] += _position;
	}	
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