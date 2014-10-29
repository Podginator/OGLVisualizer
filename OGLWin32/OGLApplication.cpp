#include "OGLApplication.h"
#include "OGLWindow.h"
#include "Resource.h"
#include <Windowsx.h>
#include "CSVParser.h"
#include <thread>

OGLApplication* OGLApplication::s_oglapp = NULL;

OGLApplication::OGLApplication()
{
	m_appwnd = NULL;
	m_hInst = 0;
	m_terminate = FALSE;
}

OGLApplication::~OGLApplication()
{
	if ( m_appwnd )
		delete m_appwnd;
}

BOOL OGLApplication::MyRegisterClass(HINSTANCE hinst)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= this->WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hinst;
	wcex.hIcon			= LoadIcon(hinst, MAKEINTRESOURCE(IDI_OGLWIN32));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszClassName	= L"OGLWindow";
	wcex.lpszMenuName = NULL;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
	if ( !RegisterClassEx ( &wcex ) )
		return FALSE;

	return TRUE;
}

OGLApplication* OGLApplication::CreateApplication(HINSTANCE hinst)
{
	if ( ! s_oglapp )
	{
		s_oglapp = new OGLApplication();

		s_oglapp->m_hInst = hinst;
		s_oglapp->MyRegisterClass(hinst);

		//Now create an OGLWindow for this application
		s_oglapp->CreateApplicationWindow(1024,768);
	}

	return s_oglapp;
}

void OGLApplication::DestroyApplication()
{
	if ( s_oglapp )
		delete s_oglapp;
}

OGLApplication* OGLApplication::GetApplication()
{
	return s_oglapp;
}

void OGLApplication::CreateApplicationWindow( int width, int height )
{
	if ( !m_appwnd  )
	{
		m_appwnd = new OGLWindow();
		m_appwnd->InitWindow(m_hInst, width, height);
		m_appwnd->SetVisible(TRUE);
	}
}

int OGLApplication::Run() {
	MSG msg;

	while (!m_terminate) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			//peek for windows message
			if (msg.message == WM_QUIT) {
				Kill();
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			m_appwnd->Render();
		}
	}


	return (int)msg.wParam;
}


void OGLApplication::Kill()
{
	m_terminate = TRUE;
}


LRESULT CALLBACK OGLApplication::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	int wmId, wmEvent;
	//Include them in the fn scope rather than the case scope 
	//so we can disable them later depending on data type.
	static HMENU menu;
	HMENU popmenu;

	static UINT FileMenu = 0;
	static UINT ChartMenu = 0;

	switch (msg) {
		//Create Menus.
	case WM_CREATE:
		menu = CreateMenu();

		popmenu = CreatePopupMenu();
		FileMenu = UINT(popmenu);
		AppendMenu(popmenu, MF_STRING, ID_CREATE_FILE, L"Open CSV File");
		AppendMenu(menu, MF_STRING | MF_POPUP, FileMenu, L"&File");

		popmenu = CreatePopupMenu();
		ChartMenu = UINT(popmenu);
		AppendMenu(popmenu, MF_STRING, ID_BARCHART, L"BarChart View");
		AppendMenu(popmenu, MF_STRING, ID_SCATTERPLOT2D, L"Scatterplot 2d View");
		AppendMenu(popmenu, MF_STRING, ID_SCATTERPLOT3D, L"Scatterplot 3d View");
		AppendMenu(popmenu, MF_STRING, ID_PIECHART, L"Pie Chart View");
		AppendMenu(menu, MF_STRING | MF_POPUP, ChartMenu, L"&Chart Views");

		SetMenu(hwnd, menu);
		break;
	case WM_COMMAND:
		switch (LOWORD(wparam)) {
		case ID_CREATE_FILE:
			EnableMenuItem(menu, FileMenu, MF_GRAYED);
			EnableMenuItem(menu, ChartMenu, MF_GRAYED);
			DrawMenuBar(hwnd);
			FileOpen openfile(std::map < LPWSTR, LPWSTR > {{ L"CSV files", L"*.csv" }, { L"ALL FILES", L"WHAFGs" }});
			if (openfile.ShowDialog()) {
				std::vector<std::vector<std::string>> res = CSVParser::Parse(openfile.getFile());
			}
			EnableMenuItem(menu, FileMenu, MF_ENABLED);
			EnableMenuItem(menu, ChartMenu, MF_ENABLED);
			DrawMenuBar(hwnd);

			break;
		}
		break;

		case WM_SIZE:
			s_oglapp->GetApplicationWindow()->Resize(LOWORD(lparam), HIWORD(lparam));
			
			break;

		case WM_CLOSE:
			s_oglapp->GetApplicationWindow()->DestroyOGLWindow();
			break;

		case WM_MOUSEMOVE:
			//inform the cursor position to OGLWindow
			s_oglapp->GetApplicationWindow()->MouseMove( GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) );
			break;

		case WM_LBUTTONUP:
			s_oglapp->GetApplicationWindow()->MouseLBUp( GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) );
			break;

		case WM_LBUTTONDOWN:
			s_oglapp->GetApplicationWindow()->MouseLBDown( GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) );
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;


		default:
			return DefWindowProc( hwnd, msg, wparam, lparam );
	}

	return 0;
}