#pragma once
#include "OGLShape.h"
class OGLRectangle : public OGLShape
{
	private:
		float _width;
		float _height;

	public:
						OGLRectangle(Vec2f position, Color color, float height, float width);
						~OGLRectangle();

		void			CenterRotate(float deg);
		bool			MouseMove( int x, int y );
		bool			MouseLBUp( int x, int y );
		bool			MouseLBDown( int x, int y );
};