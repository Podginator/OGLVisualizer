#pragma once

#include <Windows.h>
#include <string>
#include "FileOpen.h"
#include "OGLChart.h"
#include "Matrix.h"
#include "Vector.h"
#include "MathHelper.h"
#include "Utility.h"
#include "OGLPieChart.h"

class OGLWindow
{
    private:
        HWND        m_hwnd;                //handle to a window
        HDC            m_hdc;                //handle to a device context
        HGLRC        m_hglrc;            //handle to a gl rendering context

        int            m_width;
        int            m_height;
        
        //This is not an ideal place to hold geometry data
        OGLChart   *m_chart;

protected:

        HGLRC CreateOGLContext (HDC hdc);
        BOOL DestroyOGLContext();
        void InitOGLState();
        void SetClientSize();

    public:
                    OGLWindow();
                    OGLWindow(HINSTANCE hInstance, int width, int height);
                    ~OGLWindow();

        void        Render(bool thread = false);
        void        Resize( int width, int height );
        void        SetVisible( BOOL visible );
        void        DestroyOGLWindow();
        //Necessary for Windows 8.
        BOOL        InitWindow(HINSTANCE hInstance, int width, int height);
        BOOL        MouseLBDown ( int x, int y );
        BOOL        MouseLBUp ( int x, int y );
        BOOL        MouseMove ( int x, int y );
};