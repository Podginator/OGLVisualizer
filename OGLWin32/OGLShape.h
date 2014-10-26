#pragma once

#include "Renderable.h"
#include "Listener.h"
#include "MathHelper.h"
#include <math.h>
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

	//Necessary for Bounding Box
	float xMin;
	float xMax;
	float yMin;
	float yMax;

	void GetBoundingBox()
	{
		for (size_t i = 0; i < _size; i++)
		{
			if (vertexs[i].X() > xMax)
			{
				xMax = vertexs[i].X();
			}
			if (vertexs[i].X() < xMin)
			{
				xMin = vertexs[i].X();
			}
			if (vertexs[i].Y() > yMax)
			{
				yMax = vertexs[i].Y();
			}
			if (vertexs[i].Y() < yMin)
			{
				yMin = vertexs[i].Y();
			}
		}
	}

	
public: 
	OGLShape(const Vec2f& position, const Color& color, size_t size, unsigned int renderType) : _position(position), rgb(color), _size(size), _renderType(renderType)
	{
		vertexs = new Vec2f[size];
	};

	OGLShape(const Vec2f& position, const Color& color, size_t size, unsigned int renderType, Vec2f positions[]) : _position(position), _size(size), rgb(color), _renderType(renderType)
	{
		vertexs = new Vec2f[size+1];
		vertexs[0] = position;

		xMin = xMax = _position.X();
		yMin = yMax = _position.Y();

		for (size_t i = 1; i < size; i++)
		{
			vertexs[i] = positions[i - 1];
		}

		GetBoundingBox();
	}

	~OGLShape()
	{
		delete[] vertexs;
	}

	virtual void Render();
	virtual void Rotate(float deg);
	virtual void CenterRotate(float deg);
	


	bool MouseInside(int x, int y)
	{
		//First we test the bounding box cast around the object, this is a very
		//mathematically unintensive process, meaning when we loop through shapes
		//later we won't have problems.
		if (x < xMin || x > xMax || y < yMin || y > yMax) {
			return false;
		}

		return true;
	}

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