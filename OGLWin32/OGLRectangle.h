#pragma once
#include "OGLShape.h"
class OGLRectangle : public OGLShape
{
	private:
		float _width;
		float _height;

	public:
						OGLRectangle(const Vec2f& position, const Color& color, float height, float width);
						~OGLRectangle();

		void			CenterRotate(float deg);
};