#include "OGLRectangle.h"

OGLRectangle::OGLRectangle(Vec2f position, Color color, float height, float width)
:OGLShape(position, color, 4, GL_QUADS)
{
	//init the OGLRectangle to a fixed size
	vertexs[0] = Vec2f(position);
	vertexs[1] = Vec2f(position.X() + width, position.Y());
	vertexs[2] = Vec2f(position.X() + width, position.Y() + height);
	vertexs[3] = Vec2f(position.X(), position.Y() + height);
	_height = height;
	_width = width;
}

OGLRectangle::~OGLRectangle()
{

}

void OGLRectangle::CenterRotate(float deg)
{
	//Move them towards the center. 
	for (int i = 0; i < _size; i++)
	{
		vertexs[i] -= Vec2f((_width*0.5f), (_height*0.5f));
	}

	OGLShape::CenterRotate(deg);

	for (int i = 0; i < _size; i++)
	{
		vertexs[i] += Vec2f((_width*0.5f), (_height*0.5f));
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