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
	//What do I exactly need to do here? 
	//translate it back towards the center, so, move all points back by 0,0 then rotate
	Matrix<float> rotMat = MathHelper<float>::Matrix2Dtransform(deg);

	for (int i = 0; i < _size; i++)
	{
		vertexs[i] -= _position;
		vertexs[i] = rotMat * vertexs[i];
		vertexs[i] += _position;
	}

		

}