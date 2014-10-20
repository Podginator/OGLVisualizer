#pragma once

#include "Renderable.h"
#include "Listener.h"
#include "Vector.h"
#include "Matrix.h"
#include "MathHelper.h"
#include "Color.h"

class OGLShape : public Renderable, public Listener
{
protected:
	Vec2f _position;
	Color rgb;
	Vec2f* vertexs;
	int _size;
	unsigned int _renderType;
	void RenderVertexs();
	
public: 
	OGLShape(Vec2f position, std::string hexColor, int size, unsigned int renderType) : _position(position), rgb(hexColor), _size(size), _renderType(renderType)
	{
		vertexs = new Vec2f[size];
	};

	OGLShape(Vec2f position, Color color, int size, unsigned int renderType) : _position(position), rgb(color), _size(size), _renderType(renderType)
	{
		vertexs = new Vec2f[size];
	};

	~OGLShape()
	{
		delete[] vertexs;
	}

	virtual void Render();
	virtual void Rotate(float deg);
	virtual void CenterRotate(float deg);

};