#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <stdio.h>
#include "Renderable.h"
#include "Listener.h"
#include "Vec2.h"
#include "Matrix.h"
#include "MathHelper.h"
#include "Color.h"

class OGLShape : public Renderable, public Listener
{
protected:
	Vec2 _position;
	Color rgb;
	Vec2* vertexs;
	int _size;
	void RenderVertexs();

public: 
	OGLShape(Vec2 position, std::string hexColor, int size) : _position(position), rgb(hexColor), _size(size)
	{
		vertexs = new Vec2[size];
	};

	OGLShape(Vec2 position, Color color, int size) : _position(position), rgb(color), _size(size)
	{
		vertexs = new Vec2[size];
	};

	~OGLShape()
	{
		delete[] vertexs;
	}

	virtual void Rotate(float deg);
	virtual void CenterRotate(float deg);

};