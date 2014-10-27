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
	float xBot;
	float xTop;
	float yBot;
	float yTop;

	void GetBoundingBox()
	{
		for (size_t i = 0; i < _size; i++)
		{
			if (vertexs[i].X() > xTop)
			{
				xTop = vertexs[i].X();
			}
			if (vertexs[i].X() < xBot)
			{
				xBot = vertexs[i].X();
			}
			if (vertexs[i].Y() > yTop)
			{
				yTop = vertexs[i].Y();
			}
			if (vertexs[i].Y() < yBot)
			{
				yBot = vertexs[i].Y();
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

		xBot = xBot = _position.X();
		yBot = yTop = _position.Y();

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
		if (x < xBot || x > xTop || y < yBot || y > yTop) 
		{
			return false;
		}

		int in = 0;
		//We start at point vertexs[_size] connecting to vertexs[0]
		size_t  k = _size - 1;
		//Then we have to loop through all the Vertexs we have
		//Based on the lecture from 20/10/2014
		for (size_t i = 0; i < _size; i++)
		{
			//First we check whether it is between the vertexs Y locations, if not, no point of continuing.
			if (((vertexs[i].Y() > y) && (vertexs[k].Y() < y)) || ((vertexs[i].Y() < y) && (vertexs[k].Y() > y)))
			{
				//Then we check if the X location is less than the X location of the point between Vec[i] and Vec[k], if it is, it will eventually intersect.
				//calculating where that would be based on the Y position. Based on
				// http://gamedev.stackexchange.com/a/57746
				if (x < vertexs[i].X() + (vertexs[k].X() - vertexs[i].X()) * (y - vertexs[i].Y()) / (vertexs[k].Y() - vertexs[i].Y()))
				{
					in++;
				}
			}
			//Then we make sure that for the next cycle K is the one before the previous. ie the vector that i was this time.
			k = i;
		}

		return (in%2);
	}

	bool MouseMove(int x, int y)
	{
		//printf("%d, %d", x, y);
		//MouseInside(x, y);
		return true;
	}
	bool MouseLBUp(int x, int y)
	{
		return true;
	}
	bool MouseLBDown(int x, int y)
	{
		printf("%d,%d\n",x, y);
		printf("%d", MouseInside(x, y));
		
		if (MouseInside(x, y))
		{
			rgb = Color(1, 0, 0);
		}
		return true;
	}

};