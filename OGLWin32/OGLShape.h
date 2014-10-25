#pragma once

#include "Renderable.h"
#include "Listener.h"
#include "MathHelper.h"
#include "Color.h"

class OGLShape : public Renderable, public Listener
{
protected:
	Vec2f _position;
	Color rgb;
	Vec2f* vertexs;
	size_t _size;
	unsigned int _renderType;
	void RenderVertexs();
	
public: 
	OGLShape(const Vec2f& position, const Color& color, size_t size, unsigned int renderType) : _position(position), rgb(color), _size(size), _renderType(renderType)
	{
		vertexs = new Vec2f[size];
	};

	OGLShape(const Vec2f& position, const Color& color, size_t size, unsigned int renderType, Vec2f positions[]) : _position(position), _size(size), rgb(color), _renderType(renderType)
	{
		vertexs = new Vec2f[size+1];
		vertexs[0] = position;
		for (size_t i = 1; i < size; i++)
		{
			vertexs[i] = positions[i - 1];
		}
	}

	~OGLShape()
	{
		delete[] vertexs;
	}

	virtual void Render();
	virtual void Rotate(float deg);
	virtual void CenterRotate(float deg);

	bool MouseMove(int x, int y)
	{
		return true;
	}
	bool MouseLBUp(int x, int y)
	{
		return true;
	}
	bool MouseLBDown(int x, int y)
	{
		return true;
	}

};