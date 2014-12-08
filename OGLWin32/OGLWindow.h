#pragma once

#include <Windows.h>
#include <string>
#include "FileOpen.h"
#include "OGLChart.h"
#include "Matrix.h"
#include "Vector.h"
#include "MathHelper.h"
#include "Utility.h"
#include "CSVParser.h"
#include "OGLChart.h"
#include "OGLPieChart.h"
#include "OGLBarChart.h"
#include "OGLSpiderChart.h"
#include "OGLScatterplot.h"
#include "OGLBoxChart.h"
#include "OGLScatterplot3d.h"
#include "OGLLineChart.h"
#include "OGLCube3D.h"

class OGLWindow
{
    private:
        HWND m_hwnd;                //handle to a window
        HDC m_hdc;                //handle to a device context
        HGLRC m_hglrc;            //handle to a gl rendering context

        
     
protected:

        HGLRC CreateOGLContext (HDC hdc);
        BOOL DestroyOGLContext();
        void InitOGLState();
        void SetClientSize();

public:
        static int m_width;
        static int m_height;
        OGLWindow();
        OGLWindow(HINSTANCE hInstance, int width, int height);
        ~OGLWindow();

        void Render(bool thread = false);
        void Resize( int width, int height );
        void SetVisible( BOOL visible );
        void DestroyOGLWindow();
        void RemoveCharts();
        void OrganizeCharts();
        void ResetCharts();
        //Necessary for Windows 8.

        std::vector<OGLChart*> charts;
        OGLCube cube;
        DataTable data;

        BOOL InitWindow(HINSTANCE hInstance, int width, int height);
        BOOL MouseLBDown ( int x, int y );
        BOOL MouseLBUp ( int x, int y );
        BOOL MouseMove ( int x, int y );
        BOOL MouseWheel(float delta);
};