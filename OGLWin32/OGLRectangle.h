#pragma once
#include "OGLShape.h"
class OGLRectangle : public OGLShape
{
	private:
		float _width;
		float _height;

	public:
						OGLRectangle(Vec2 position, Color color, float height, float width);
						OGLRectangle(Vec2 position, std::string hexColor, float height, float width);
						~OGLRectangle();

		void			Render();
		void			CenterRotate(float deg);
		bool			MouseMove( int x, int y );
		bool			MouseLBUp( int x, int y );
		bool			MouseLBDown( int x, int y );
};