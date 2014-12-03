#pragma once
#include "OGLScatterplot3d.h"
#include "OGLRectangle3D.h"

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
    text = new OGLText[12];
    _border = OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750);
    
    dataDist[new OGLLine(Vec2f(-300, -150), Color(0.0, 0.0, 0.0), Vec2f(-300, 200))] = nullptr;
    dataDist[new OGLLine(Vec2f(-300, -150), Color(0.0, 0.0, 0.0), Vec2f(300, -150))] = nullptr;
    dataDist[new OGLLine3D(Vec3f(-300, -150, -1), Color(0, 0, 0), Vec3f(-300, -150, -5))] = nullptr;



    textSize++;
    text[textSize] = OGLText(Vec3f(-350, -150, -1), Color(0, 0, 0), "1", 12);
    textSize++;
    text[textSize] = OGLText(Vec3f(-350, -150, -1.5), Color(0, 0, 0), "1.5",  12);
    textSize++;
    text[textSize] = OGLText(Vec3f(-350, -150, -2), Color(0, 0, 0), "2", 12);
    textSize++;
    text[textSize] = OGLText(Vec3f(-350, -150, -2.5), Color(0, 0, 0), "2.5",  12);
    textSize++;
    text[textSize] = OGLText(Vec3f(-350, -150, -3), Color(0, 0, 0), "3", 12);
    textSize++;
    text[textSize] = OGLText(Vec3f(-350, -150, -3.5), Color(0, 0, 0), "3.5", 12);
    textSize++;
    text[textSize] = OGLText(Vec3f(-350, -150, -4), Color(0, 0, 0), "4", 12);
    textSize++;
    text[textSize] = OGLText(Vec3f(-350, -150, -4.5), Color(0, 0, 0), "4.5", 12);
    textSize++;
    text[textSize] = OGLText(Vec3f(-350, -150, -5), Color(0, 0, 0), "5", 12);
    textSize++;


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


    dataDist[new OGLLine3D(Vec3f(-300, -150, -1), Color(0.0, 0.0, 0.0), Vec3f(-300, 200, -1))] = nullptr;
    dataDist[new OGLLine3D(Vec3f(-300, -150, -1), Color(0.0, 0.0, 0.0), Vec3f(300, -150, -1))] = nullptr;
    dataDist[new OGLLine3D(Vec3f(-300, -150, -1), Color(0, 0, 0), Vec3f(-300, -150, -5))] = nullptr;

    float maxX = data[0].Max;
    float maxY = data[1].Max;
    float maxZ = data[2].Max;

    for (int i = 0; i <= 10; i++)
    {
        float height = (-150) + (350 / (10))*i;
        float width = (-300) + (600 / 10)*i;
        float depth = 1 + (5.f / 10.f)*(10-i);
        printf("%f\n", depth);
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
        sg << std::fixed << std::setprecision(1) << (maxZ / 10)*(10-i);
        text[textSize] = OGLText(Vec3f(-340, -150, -(depth)), Color(0, 0, 0), sg.str(), 10);
        textSize++;
    }


    for (int i = 0; i < data[0].size; i++)
    {
        OGLShape* index;
        float y = 0;
        float x = 0;
        float z = -1;

        if (data[0].rawData[i].isA<float>())
        {
            x = (600 * (data[0].rawData[i].asA<float>() / maxX)) - 300;
        }
        else if (data[0].rawData[i].isA<int>())
        {
            x = (600 * (float(data[0].rawData[i].asA<int>()) / maxX)) - 300;
        }

        if (data[1].rawData[i].isA<float>())
        {
            y = (350 * (data[1].rawData[i].asA<float>() / maxY)) - 150;
        }
        else if (data[1].rawData[i].isA<int>())
        {
            y = (350 * (float(data[1].rawData[i].asA<int>()) / maxY)) - 150;
        }

        if (data[2].rawData[i].isA<float>())
        {
            z = -(5 * (data[2].rawData[i].asA<float>() / maxZ)) -1;
        }
        else if (data[2].rawData[i].isA<int>())
        {
            z = -(5* (float(data[2].rawData[i].asA<int>()) / maxZ)) - 1;
        }

        printf("z::::%f Y:::%f, X::::%f\n", z, y, x);

        index = new OGLRectangle3D(Vec3f(x, y, z), Color(0.f, 0.f, 0.f, 0.5f), 3, 3);
        index->CenterRotate(45.0f);
        //index = new OGLCircle(Vec2f(x, y), Color(0, 0, 0), 5);
        dataDist[index] = new DataCell(std::string(data[0].Name() + " " + data[0].rawData[i].getString() + ":: " + data[1].Name() + " " + data[1].rawData[i].getString() + " " + data[2].Name() + " " + data[2].rawData[i].getString()));
    }
    textSize += 2;
    text[22] = OGLText(Vec2f(-350, 230), Color(0, 0, 0), data[1].Name(), "arial.glf", 12);
    text[23] = OGLText(Vec2f(0, -170), Color(0, 0, 0), data[0].Name(), "arial.glf", 12);

    Scale(scale);
    Move(-_relativePos.X(), -_relativePos.Y());
    printf("Done");
    
}

bool OGLScatterplot3D::MouseWheel(float deg)
{
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

        for (size_t k = 2; k < 32; k+=3)
        {
            printf("%d\n", k);
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