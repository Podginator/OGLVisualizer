#pragma once
#include "OGLScatterplotV2.h"
#include <gl/GLU.h>


void OGLScatterplot3DV2::AddDataSource(DataColumn col)
{
	if (col.Stores() == DataColumn::Storage::Categorical){ return; }
	if (data.size() == 3)
	{
		data.pop_back();
	}
	data.insert(data.begin(), col);
	InitElements();
}

OGLScatterplot3DV2::OGLScatterplot3DV2()
{
	textSize = 1;
	text = new OGLText[1];
	text[0] = OGLText(Vec2f(-1.5, -0), Color(0, 0, 0), "Scatterplot3D, add " + std::to_string(3 - data.size()) + " Data Columns(Numerical) to start", "arial.glf", 0.09);

}

bool OGLScatterplot3DV2::MouseLBDown(int x, int y)
{
	OGLChart::MouseLBDown(x, y);

	return _border.MouseInside(x - xOff, y - yOff);
}


void OGLScatterplot3DV2::Move(float x, float y)
{
	if (Listener::keys[16])
	{
		OGLChart::Move(x, y);
		xOff -= x;
		yOff -= y;
		return;
	}
	xOff += x;
	yOff += y;


}

void OGLScatterplot3DV2::InitElements()
{
	//Clear everything

	Clear();

	if (data.size() < 3)
	{
		textSize = 1;
		text = new OGLText[1];
		text[0] = OGLText(Vec2f(-1.5, 0), Color(0, 0, 0), "Scatterplot3D, add " + std::to_string(3 - data.size()) + " Data Columns(Numerical) to start", "arial.glf", 0.09);
		return;
	}

	text = new OGLText[36];


	dataDist[new OGLLine3D(Vec3f(-1.0f, -1.0f, 1.0f), Color(0.0, 0.0, 0.0), Vec3f(1.0f, -1.0f, 1.0f))] = nullptr;
	dataDist[new OGLLine3D(Vec3f(-1.0f, -1.0f, 1.0f), Color(0.0, 0.0, 0.0), Vec3f(-1.0f, 1.0f, 1.0f))] = nullptr;
	dataDist[new OGLLine3D(Vec3f(-1.0, -1.0f, 1.0f), Color(0, 0, 0), Vec3f(-1.0f, -1.0f, -1.0f))] = nullptr;


	float maxX = data[0].Max;
	float maxY = data[1].Max;
	float maxZ = data[2].Max;

	for (int i = 0; i <= 10; i++)
	{
		float height = -1.f + (2.f*(1.f / (10.f)))*i;
		float width = -1.f + (2.f * (1.f / (10.f)))*i;
		float depth = -1.f + 2 * (1.f / 10.f)*(10 - i);

		std::stringstream ss;
		ss << std::fixed << std::setprecision(1) << (maxY / 10)*i;
		text[textSize] = OGLText(Vec3f(-1.15, height, 1), Color(0, 0, 0), ss.str(), 0.03);
		textSize++;

		std::stringstream sf;
		sf << std::fixed << std::setprecision(1) << (maxX / 10)*i;
		text[textSize] = OGLText(Vec3f(width, -1.f, 1), Color(0, 0, 0), sf.str(), 0.03);
		textSize++;

		std::stringstream sg;
		sg << std::fixed << std::setprecision(1) << (maxZ / 10)*(10 - i);
		text[textSize] = OGLText(Vec3f(-1.0, -1.0, -(depth)), Color(0, 0, 0), sg.str(), 0.03);
		textSize++;
	}


	for (int i = 0; i < data[0].size; i++)
	{
		OGLShape* index;
		float y = 0;
		float x = 0;
		float z = -1;

		if (data[0].data[i].isA<float>())
		{
			x = -1 + (2 * (data[0].data[i].asA<float>() / maxX));
			//Have to get these values between 1 and -1. 
			//Ho
		}
		else if (data[0].data[i].isA<int>())
		{
			x = -1 + (2 * (data[0].data[i].asA<int>() / maxX));
		}

		if (data[1].data[i].isA<float>())
		{
			y = -1 + (2 * (data[1].data[i].asA<float>() / maxY));
		}
		else if (data[1].data[i].isA<int>())
		{
			y = -1 + (2 * (data[1].data[i].asA<int>() / maxY));
		}

		if (data[2].data[i].isA<float>())
		{
			z = 1 - (2 * (data[2].data[i].asA<float>() / maxZ));
		}
		else if (data[2].data[i].isA<int>())
		{
			z = 1 - (2 * (data[2].data[i].asA<int>() / maxZ));
		}


		index = new OGLRectangle3D(Vec3f(x, y, z), Color(0.f, 0.f, 0.f, 0.5f), 0.03f, 0.03f);
		index->CenterRotate(45.0f);
		//index = new OGLCircle(Vec2f(x, y), Color(0, 0, 0), 5);
		dataDist[index] = new DataCell(std::string(data[0].Name() + " " + data[0].data[i].getString() + ":: " + data[1].Name() + " " + data[1].data[i].getString() + " " + data[2].Name() + " " + data[2].data[i].getString()));
	}
	textSize += 3;
	text[33] = OGLText(Vec3f(-1.0f, 1.1f, 1.0f), Color(0, 0, 0), data[1].Name(), "arial.glf", 0.03);
	text[34] = OGLText(Vec3f(0, -1.1f, 1.0f), Color(0, 0, 0), data[0].Name(), "arial.glf", 0.03);
	text[35] = OGLText(Vec3f(-1.0f, -1.0f, -1.1f), Color(0, 0, 0), data[2].Name(), 0.03);

	Scale(scale);
	Move(-_relativePos.X(), -_relativePos.Y());
	printf("Done\n");

}

void OGLScatterplot3DV2::Render()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
    glFrustum((-0.5*Renderable::RenderX - xOff), (0.5*Renderable::RenderX - (xOff)), (-0.5 * Renderable::RenderY - (yOff)), (0.5 * Renderable::RenderY - (yOff)), 1.f, 500.f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	static float rotqube = 0;

	_border.Render();



	//So we could do it on a scale of 1 - -1. Then scale. It does though, for rotational purposes.
	glScalef(600, 350, 1);
	glTranslatef(0.0f, 0.0f, -3.0f);

	if (xRot != 0)
		glMultMatrixf(MathHelper::Matrix4DtransformY(xRot).data);
	if (yRot != 0)
		glMultMatrixf(MathHelper::Matrix4DtransformX(yRot).data);

	std::map<OGLShape*, DataCell*>::iterator mapIt = dataDist.begin();
	while (mapIt != dataDist.end())
	{
		mapIt->first->Render();
		mapIt++;
	}

	if (highlightText)
	{
		highlightText->Render();
	}

	for (size_t k = 0; k < textSize; k++)
	{
		text[k].Render();
	}


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}

bool OGLScatterplot3DV2::MouseWheel(float deg)
{
	if (Listener::keys[90])
	{
		if (deg > 0)
		{
			xRot += 0.3;
		}
		else
		{
			xRot -= 0.3;
		}

		return true;
	}

	if (Listener::keys[88])
	{
		if (deg > 0)
		{
			yRot += 0.3;
		}
		else
		{
			yRot -= 0.3;
		}

		return true;
	}

	if (Listener::keys[16])
	{
		std::map<OGLShape*, DataCell*>::iterator mapIt = dataDist.begin();
		while (mapIt != dataDist.end())
		{
			OGLShape3D* shape = dynamic_cast<OGLShape3D*>(mapIt->first);
			if (shape && Listener::keys[16])
			{
				if (deg > 0)
				{
					shape->MoveZ(0.1);
				}
				else
				{
					shape->MoveZ(-0.1);
				}
			}
			mapIt++;
		}

		for (size_t k = 2; k < 32; k += 3)
		{
			if (deg > 0)
			{
				text[k].MoveZ(0.1);
			}
			else
			{
				text[k].MoveZ(-0.1);
			}
		}

		return true;
	}
	else
	{
		OGLChart::MouseWheel(deg);
	}

	return true;
}