#include "OGLRectangle.h"

OGLRectangle::OGLRectangle(Vec2 position, Color color, float height, float width)
:OGLShape(position, color, 4)
{
	//init the OGLRectangle to a fixed size
	vertexs[0] = Vec2(position);
	vertexs[1] = Vec2(position.X() + width, position.Y());
	vertexs[2] = Vec2(position.X() + width, position.Y() + height);
	vertexs[3] = Vec2(position.X(), position.Y() + height);
	_height = height;
	_width = width;
}

OGLRectangle::~OGLRectangle()
{

}

void OGLRectangle::Render()
{
	glBegin(GL_QUADS);							
		glColor3f(rgb.red, rgb.green, rgb.blue);
		for (int i = 0; i < _size; i++)
		{
			glVertex2f(vertexs[i].X(), vertexs[i].Y());
		}
		glPopMatrix();
	glEnd();
}


void OGLRectangle::CenterRotate(float deg)
{
	for (int i = 0; i < _size; i++)
	{
		vertexs[i] -= Vec2((_width*0.5), 0);
		vertexs[i] -= Vec2(0, (_height*0.5));
	}

	OGLShape::CenterRotate(deg);

	for (int i = 0; i < _size; i++)
	{
		vertexs[i] += Vec2((_width*0.5), 0);
		vertexs[i] += Vec2(0, (_height*0.5));
	}

}
bool OGLRectangle::MouseMove(int x, int y)
{
	return true;
}
bool OGLRectangle::MouseLBUp( int x, int y )
{
	return true;
}
bool OGLRectangle::MouseLBDown( int x, int y )
{
	CenterRotate(1.0f);
	return true;
}

