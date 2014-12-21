#pragma once
#include "OGLScatterplot3d.h"
#include <gl/GLU.h>


void OGLScatterplot3D::AddDataSource(DataColumn col)
{
	if (col.Stores() == DataColumn::Storage::Categorical){ return; }
	if (data.size() == 3)
	{
		data.pop_back();
	}
	data.insert(data.begin(), col);
	InitElements();
}

OGLScatterplot3D::OGLScatterplot3D()
{
	textSize = 1;
	text = new OGLText[1];
	text[0] = OGLText(Vec2f(-300, 0), Color(0, 0, 0), "Scatterplot3D, add " + std::to_string(3 - data.size()) + " Data Columns(Numerical) to start", "arial.glf", 18);


}

bool OGLScatterplot3D::MouseLBDown(int x, int y)
{
	OGLChart::MouseLBDown(x, y);

	return _border.MouseInside(x - xOff, y - yOff);
}

void OGLScatterplot3D::Move(float x, float y)
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

void OGLScatterplot3D::InitElements()
{
	//Clear everything

	Clear();

	if (data.size() < 3)
	{
		textSize = 1;
		text = new OGLText[1];
		text[0] = OGLText(Vec2f(-300, 0), Color(0, 0, 0), "Scatterplot3D, add " + std::to_string(3 - data.size()) + " Data Columns(Numerical) to start", "arial.glf", 18);
		return;
	}

	text = new OGLText[36];


	dataDist[new OGLLine(Vec2f(-300, -150), Color(0.0, 0.0, 0.0), Vec2f(-300, 200))] = nullptr;
	dataDist[new OGLLine(Vec2f(-300, -150), Color(0.0, 0.0, 0.0), Vec2f(300, -150))] = nullptr;
	dataDist[new OGLLine3D(Vec3f(-300, -150, -1), Color(0, 0, 0), Vec3f(-300, -150, -5))] = nullptr;

	float maxX = data[0].Max;
	float maxY = data[1].Max;
	float maxZ = data[2].Max;

	for (int i = 0; i <= 10; i++)
	{
		float height = (-150.f) + (350.f / (10.f))*i;
		float width = (-300) + (600 / 10)*i;
		float depth = 1 + (5.f / 10.f)*(10 - i);
		dataDist[new OGLLine(Vec2f(-310, height), Color(0, 0, 0), Vec2f(-300, height))] = nullptr;

		std::stringstream ss;
		ss << std::fixed << std::setprecision(1) << (maxY / 10)*i;
		text[textSize] = OGLText(Vec2f(-350, height + 6), Color(0, 0, 0), ss.str(), 10);
		textSize++;

		dataDist[new OGLLine(Vec2f(width, -150), Color(0, 0, 0), Vec2f(width, -155))] = nullptr;
		std::stringstream sf;
		sf << std::fixed << std::setprecision(1) << (maxX / 10)*i;
		text[textSize] = OGLText(Vec2f(width, -155), Color(0, 0, 0), sf.str(), 10);
		textSize++;

		dataDist[new OGLLine(Vec2f(width, -150), Color(0, 0, 0), Vec2f(width, -155))] = nullptr;
		std::stringstream sg;
		sg << std::fixed << std::setprecision(1) << (maxZ / 10)*(10 - i);
		text[textSize] = OGLText(Vec3f(-340, -150, -(depth)), Color(0, 0, 0), sg.str(), 10);
		textSize++;
	}


	for (size_t i = 0; i < data[0].size; i++)
	{
		OGLShape* index;
		float y = 0;
		float x = 0;
		float z = -1;

		if (data[0].data[i].isA<float>())
		{
			x = (600 * (data[0].data[i].asA<float>() / maxX)) - 300;
		}
		else if (data[0].data[i].isA<int>())
		{
			x = (600 * (float(data[0].data[i].asA<int>()) / maxX)) - 300;
		}

		if (data[1].data[i].isA<float>())
		{
			y = (350 * (data[1].data[i].asA<float>() / maxY)) - 150;
		}
		else if (data[1].data[i].isA<int>())
		{
			y = (350 * (float(data[1].data[i].asA<int>()) / maxY)) - 150;
		}

		if (data[2].data[i].isA<float>())
		{
			z = -(5 * (data[2].data[i].asA<float>() / maxZ)) - 1;
		}
		else if (data[2].data[i].isA<int>())
		{
			z = -(5 * (float(data[2].data[i].asA<int>()) / maxZ)) - 1;
		}


		index = new OGLRectangle3D(Vec3f(x, y, z), Color(0.f, 0.f, 0.f, 0.5f), 3, 3);
		index->CenterRotate(45.0f);
		//index = new OGLCircle(Vec2f(x, y), Color(0, 0, 0), 5);
		dataDist[index] = new DataCell(std::string(data[0].Name() + " " + data[0].data[i].getString() + ":: " + data[1].Name() + " " + data[1].data[i].getString() + " " + data[2].Name() + " " + data[2].data[i].getString()));
	}
	textSize += 3;
	text[33] = OGLText(Vec2f(-350, 230), Color(0, 0, 0), data[1].Name(), "arial.glf", 12);
	text[34] = OGLText(Vec2f(0, -170), Color(0, 0, 0), data[0].Name(), "arial.glf", 12);
	text[35] = OGLText(Vec3f(-390, 0, -2), Color(0, 0, 0), data[2].Name(), 12);

	Scale(scale);
	Move(-_relativePos.X(), -_relativePos.Y());
	printf("Done");

}

void OGLScatterplot3D::Render()
{
	SetUpMatrices();

    OGLChart::Render();

	RestoreMatrices();
}

bool OGLScatterplot3D::MouseWheel(float deg)
{
	if (Listener::keys[90])
	{
		if (deg > 0)
		{
			xRot += 0.0001f;
		}
		else
		{
			xRot -= 0.0001f;
		}

		return true;
	}

	if (Listener::keys[88])
	{
		if (deg > 0)
		{
			yRot += 0.0001f;
		}
		else
		{
			yRot -= 0.0001f;
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
					shape->MoveZ(0.1f);
				}
				else
				{
					shape->MoveZ(-0.1f);
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