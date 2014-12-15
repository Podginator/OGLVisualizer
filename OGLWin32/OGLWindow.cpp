#include "OGLWindow.h"
#include "Resource.h"
#include <gl/GL.h>
#include <gl/GLU.h>;

OGLWindow::OGLWindow()
{
    
}

OGLWindow::~OGLWindow()
{
    DestroyOGLWindow();
}

OGLWindow::OGLWindow(HINSTANCE hInstance, int width, int height)
{
    InitWindow(hInstance, width, height);
}

HGLRC OGLWindow::CreateOGLContext(HDC hdc)
{
    unsigned int pixelformat;
    HGLRC hglrc;

    static PIXELFORMATDESCRIPTOR pfd = 
    {
        sizeof(PIXELFORMATDESCRIPTOR),                // Size Of This Pixel Format Descriptor
        1,                                            // Version Number
        PFD_DRAW_TO_WINDOW |                        // Format Support Window
        PFD_SUPPORT_OPENGL |                        // Format Support OpenGL
        PFD_DOUBLEBUFFER,                            // Must Support Double Buffering
        PFD_TYPE_RGBA,                                // Request RGBA Format
        32,                                            // Color Depth
        0, 0, 0, 0, 0, 0,                            // Color Bits mask
        0,                                            // No Alpha Buffer
        0,                                            // Shift Bit Ignored
        0,                                            // No Accumulation Buffer
        0, 0, 0, 0,                                    // Accumulation Bits Ignored
        16,                                            // Z-Buffer depth
        0,                                            // Stencil Buffer
        0,                                            // Auxiliary Buffer
        PFD_MAIN_PLANE,                                // Main Drawing Layer
        0,                                            // Reserved
        0, 0, 0                                        // Layer Masks Ignored
    };

    if (!(pixelformat=ChoosePixelFormat(hdc,&pfd)))
    {
        return 0;
    }

    if(!SetPixelFormat(hdc,pixelformat,&pfd))
    {
        return 0;
    }

    if (!(hglrc=wglCreateContext(hdc)))
    {
        return 0;
    }

    if(!wglMakeCurrent(hdc,hglrc))
    {
        return 0;
    }

    return hglrc;
}

void OGLWindow::RemoveCharts()
{
    for (size_t i = 0; i < charts.size(); i++)
    {
        charts[i]->Destroy();
        delete charts[i];
    }

    charts.clear();
}

void OGLWindow::DestroyOGLWindow()
{
    DestroyOGLContext();

    DestroyWindow( m_hwnd );

    m_hwnd = NULL;
    m_hdc = NULL;
}

BOOL OGLWindow::DestroyOGLContext()
{
    if ( m_hglrc )
    {
        wglMakeCurrent( NULL, NULL );
        wglDeleteContext( m_hglrc );
        m_hglrc = NULL;
    }
    
    if ( !ReleaseDC ( m_hwnd, m_hdc ) )
        return FALSE;

    return TRUE;
}

BOOL OGLWindow::InitWindow(HINSTANCE hInstance, int width, int height)
{
    m_hwnd = CreateWindowEx( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
        L"OGLWindow", L"OGL Visualizer", WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
        0, 0, width, height, NULL, NULL, hInstance, NULL);

    if ( ! m_hwnd )
        return FALSE;

    m_hdc = GetDC( m_hwnd );

    if ( !(m_hglrc = CreateOGLContext( m_hdc )) )
        return FALSE;
    
    RECT clientRect;
    GetClientRect(m_hwnd, &clientRect);

    m_width = clientRect.right;
    m_height = clientRect.bottom;

    return TRUE;
}

void OGLWindow::SetVisible ( BOOL visible )
{
    ShowWindow ( m_hwnd, visible? SW_SHOW : SW_HIDE );
}

void OGLWindow::Render(bool thread)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    for (size_t i = 0; i < charts.size(); i++)
    {
        charts[i]->Render();
    }

    glFlush();

    SwapBuffers(m_hdc);
    return;
}

void OGLWindow::Resize( int width, int height )
{

    RECT clientRec;
    GetClientRect(m_hwnd, &clientRec);
    Renderable::RenderY = m_height = clientRec.bottom;
    Renderable::RenderX = m_width = clientRec.right;
    

    glViewport(0, 0, m_width, m_height);
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glOrtho( 0, width, 0, height, -1.0, 1.0);
    
    //0 is the center point.
    glFrustum(-0.5*OGLWindow::m_width, 0.5*OGLWindow::m_width, -0.5*OGLWindow::m_height, 0.5*OGLWindow::m_height, 1.f, 1000.f);
    //gluPerspective(120, (0.5*m_width) / (0.5*m_height), 1.f, 100.f);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    return;
}

void OGLWindow::InitOGLState()
{
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
}

BOOL OGLWindow::MouseLBDown ( int x, int y )
{

    for (int i = charts.size()-1; i>=0; --i)
    {
        if (charts[i]->MouseLBDown(x - (m_width >> 1), (-y) - (-m_height >> 1)))
        {
            if (i != charts.size()-1)
            {
                std::swap(charts[charts.size() - 1], charts[i]);
            }
            break;
        }
    }
    return TRUE;
}

void OGLWindow::ResetCharts()
{
    for (int i = 0; i < charts.size(); ++i)
    {
        float backToOne = (700.f / charts[i]->scale) / 700.f;
        charts[i]->Scale(backToOne);
        charts[i]->scale = 1.0f;
        charts[i]->Move(-375 - charts[i]->_border._position.X(), -250 - charts[i]->_border._position.Y());
        charts[i]->_relativePos = Vec2f(0, 0);
        
    }
}

void OGLWindow::OrganizeCharts()
{
    //We want to have 3 per row of window. 
    //So we have to calculate width and height necessary. 

    //So.. We have a few things we can know. 
    //A chart, generally speaking, is 700w*500h or 1.4 aspect ratio.

    //I want to limit the amount of charts per row to be three, and have the charts underneath be immediately underneath the ones above.
    ResetCharts();
    int size = charts.size() < 3 ? charts.size() : 3;
    float maxWidth = float(m_width) / (700.f*size);

    float xOffset = 0;
    float yOffset = 0;
    for (int i = 0; i < charts.size(); ++i)
    {
        charts[i]->Move(375, -250);
        charts[i]->Scale(maxWidth);
        charts[i]->scale = maxWidth;
        charts[i]->Move((-float(m_width)/2.f)+xOffset, (float(m_height)/2.f)-yOffset);
        xOffset += (maxWidth * 700);
        if ((i+1) % 3 == 0 && i != 0)
        {
            yOffset += (maxWidth*500.f);
            xOffset = 0;
        }


    }
}

BOOL OGLWindow::MouseLBUp ( int x, int y )
{
    if (charts.size() > 0)
    {
        Listener *plistener = static_cast<Listener*>(charts[charts.size() - 1]);
        plistener->MouseLBUp(x - (m_width >> 1), (-y) - (-m_height >> 1));
    }

    return TRUE;
}

BOOL OGLWindow::MouseMove ( int x, int y )
{
    if (charts.size() > 0)
    {
        Listener *plistener = static_cast<Listener*>(charts[charts.size() - 1]);
        plistener->MouseMove(x - (m_width >> 1), (-y) - (-m_height >> 1));
    }
    
    return TRUE;
}

BOOL OGLWindow::MouseWheel(float delta)
{
    if (charts.size() > 0)
    {
        Listener *plistener = static_cast<Listener*>(charts[charts.size() - 1]);
        int scale = delta > 120.f ? -1 : 1;
        plistener->MouseWheel(scale);
    }
    return TRUE;
}