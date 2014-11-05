#pragma once

#include <Windows.h>
#include <thread>
class OGLWindow;

//Define OGLApplication as a singleton
class OGLApplication
{
    private:
        OGLWindow* m_appwnd;
        BOOL m_terminate;
        static OGLApplication* s_oglapp;
        OGLApplication();
        virtual ~OGLApplication();
        void CreateApplicationWindow(int width, int height );
        BOOL MyRegisterClass(HINSTANCE hinst);
        std::thread RenderThread;
        bool Running;
    public:
        HINSTANCE m_hInst;
        static OGLApplication* CreateApplication(HINSTANCE hInst);
        static void DestroyApplication();
        static OGLApplication* GetApplication();
        int Run();
        void Kill();

        inline OGLWindow* GetApplicationWindow()
        {
            return m_appwnd;
        }
        static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};