#include "OGLWindow.h"
#include "Resource.h"
#include <gl/GL.h>



OGLWindow::OGLWindow()
{
    
}

OGLWindow::~OGLWindow()
{
    DestroyOGLWindow();
    
    //Clean up the renderable
    delete m_chart;
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
        L"OGLWindow", L"OGLWindow", WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
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

    //Instantiate a Renderable as OGLRectangle
    
    m_chart = new OGLPieChart(new DataColumnString(20));
    return TRUE;
}

void OGLWindow::SetVisible ( BOOL visible )
{
    ShowWindow ( m_hwnd, visible? SW_SHOW : SW_HIDE );
}

void OGLWindow::Render(bool thread)
{

    //Debug(thread ? "Thread" : "Normal");

    Renderable* prenderable = static_cast<Renderable*>(m_chart);

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    prenderable->Render();

    glFlush();

    SwapBuffers(m_hdc);
    return;
}

void OGLWindow::Resize( int width, int height )
{

    RECT clientRec;
    GetClientRect(m_hwnd, &clientRec);
    m_height = clientRec.bottom;
    m_width = clientRec.right;

    glViewport(0, 0, m_width, m_height);
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glOrtho( 0, width, 0, height, -1.0, 1.0);
    
    //0 is the center point.
    glOrtho(-0.5*width, 0.5*width, -0.5*height, 0.5*height, -1.0, 1.0);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    return;
}

void OGLWindow::InitOGLState()
{
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

BOOL OGLWindow::MouseLBDown ( int x, int y )
{

    return TRUE;
}

BOOL OGLWindow::MouseLBUp ( int x, int y )
{
    Listener *plistener = static_cast<Listener*>(m_chart);

    plistener->MouseLBDown(x - (m_width >> 1), (-y) - (-m_height >> 1));

    return TRUE;
}

BOOL OGLWindow::MouseMove ( int x, int y )
{
    Listener *plistener = static_cast<Listener*>(m_chart);
    plistener->MouseMove(x - (m_width >> 1), (-y) - (-m_height >> 1));
    return TRUE;
}