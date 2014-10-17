#pragma once

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
	unsigned int _renderType;
	void RenderVertexs();
	
public: 
	OGLShape(Vec2 position, std::string hexColor, int size, unsigned int renderType) : _position(position), rgb(hexColor), _size(size), _renderType(renderType)
	{
		vertexs = new Vec2[size];
	};

	OGLShape(Vec2 position, Color color, int size, unsigned int renderType) : _position(position), rgb(color), _size(size), _renderType(renderType)
	{
		vertexs = new Vec2[size];
	};

	~OGLShape()
	{
		delete[] vertexs;
	}

	virtual void Render();
	virtual void Rotate(float deg);
	virtual void CenterRotate(float deg);

};