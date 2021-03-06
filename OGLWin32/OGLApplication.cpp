#include "OGLApplication.h"
#include "OGLWindow.h"
#include "Resource.h"
#include <Windowsx.h>
#include "CSVParser.h"
#include "DataTable.h"
#include "InputBox.h"
#include <thread>


OGLApplication* OGLApplication::s_oglapp = NULL;

HINSTANCE OGLApplication::m_hInst = NULL;

OGLApplication::OGLApplication()
{
	m_appwnd = NULL;
	m_hInst = 0;
	m_terminate = FALSE;
}

OGLApplication::~OGLApplication()
{
	if (m_appwnd)
		delete m_appwnd;
}

BOOL OGLApplication::MyRegisterClass(HINSTANCE hinst)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = this->WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinst;
	wcex.hIcon = LoadIcon(hinst, MAKEINTRESOURCE(IDI_OGLWIN32));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszClassName = L"OGLWindow";
	wcex.lpszMenuName = NULL;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	if (!RegisterClassEx(&wcex))
		return FALSE;

	return TRUE;
}

OGLApplication* OGLApplication::CreateApplication(HINSTANCE hinst)
{
	if (!s_oglapp)
	{
		s_oglapp = new OGLApplication();

		s_oglapp->m_hInst = hinst;
		s_oglapp->MyRegisterClass(hinst);

		//Now create an OGLWindow for this application
		s_oglapp->CreateApplicationWindow(1024, 768);
	}

	return s_oglapp;
}

void OGLApplication::DestroyApplication()
{
	if (s_oglapp)
		delete s_oglapp;
}

OGLApplication* OGLApplication::GetApplication()
{
	return s_oglapp;
}

void OGLApplication::CreateApplicationWindow(int width, int height)
{
	if (!m_appwnd)
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
	static UINT DataMenu = 0;
	static UINT EditMenu = 0;

	switch (msg) {
		//Create Menus.
	case WM_CREATE:
		menu = CreateMenu();
		popmenu = CreatePopupMenu();

		FileMenu = UINT(popmenu);
		InsertMenu(popmenu, 1, MF_STRING, ID_CREATE_FILE, L"OpenCSV");
		InsertMenu(menu, 1, MF_STRING | MF_POPUP, FileMenu, L"&File");

		popmenu = CreatePopupMenu();
		ChartMenu = UINT(popmenu);
		AppendMenu(popmenu, MF_STRING, ID_PIECHART, L"Pie Chart View");
		AppendMenu(popmenu, MF_STRING, ID_BARCHART, L"BarChart View");
		AppendMenu(popmenu, MF_STRING, ID_BARCHART, L"SpiderChart View");
		AppendMenu(popmenu, MF_STRING, ID_SCATTERPLOT2D, L"Scatterplot 2d View");
		AppendMenu(popmenu, MF_STRING, ID_SCATTERPLOT3D, L"Line Graph View");
		AppendMenu(popmenu, MF_STRING, ID_SCATTERPLOT3D, L"Box Plot View");
		AppendMenu(popmenu, MF_STRING, ID_SCATTERPLOT3D, L"Scatterplot 3d View(2D-Esque V1)");
		AppendMenu(popmenu, MF_STRING, 1000, L"Scatterplot 3d View(3D V2)");
		AppendMenu(menu, MF_STRING | MF_POPUP, ChartMenu, L"&Add Charts");

		popmenu = CreatePopupMenu();
		EditMenu = UINT(popmenu);
		AppendMenu(popmenu, MF_STRING, ID_REMOVE_CHART, L"Remove Selected Chart");
		AppendMenu(popmenu, MF_STRING, ID_REMOVE_CHART, L"Organise Charts");
		AppendMenu(popmenu, MF_STRING, ID_REMOVE_CHART, L"Reset Charts");
		AppendMenu(popmenu, MF_STRING, ID_REMOVE_CHART, L"Remove All Charts");
		AppendMenu(popmenu, MF_STRING, ID_REMOVE_CHART, L"About Current Chart");
		AppendMenu(menu, MF_STRING | MF_POPUP, EditMenu, L"&Charts");
		EnableMenuItem(menu, EditMenu, MF_GRAYED);

		SetMenu(hwnd, menu);
		MENUINFO mi;
		memset(&mi, 0, sizeof(mi));
		mi.cbSize = sizeof(mi);
		mi.fMask = MIM_STYLE;
		mi.dwStyle = MNS_NOTIFYBYPOS;
		SetMenuInfo(menu, &mi);
		break;
	case WM_MENUCOMMAND:
		if (lparam == EditMenu)
		{
			switch (wparam)
			{
			case 0:
			{
					  OGLChart* chart = s_oglapp->GetApplicationWindow()->charts[s_oglapp->GetApplicationWindow()->charts.size() - 1];
					  s_oglapp->GetApplicationWindow()->charts.pop_back();
					  chart->Destroy();
					  delete chart;

					  if (s_oglapp->GetApplicationWindow()->charts.size() == 0)
					  {
						  EnableMenuItem(menu, EditMenu, MF_GRAYED);
						  EnableMenuItem(menu, DataMenu, MF_GRAYED);
					  }
			}
				break;
			case 1:
				s_oglapp->GetApplicationWindow()->OrganizeCharts();
				break;
			case 2:
				s_oglapp->GetApplicationWindow()->ResetCharts();
				break;
			case 3:
				s_oglapp->GetApplicationWindow()->RemoveCharts();
				if (s_oglapp->GetApplicationWindow()->charts.size() == 0)
				{
					EnableMenuItem(menu, EditMenu, MF_GRAYED);
					EnableMenuItem(menu, DataMenu, MF_GRAYED);
				}
				break;
			case 4:
				s_oglapp->GetApplicationWindow()->AboutChart();
			}
		}
		if (lparam == FileMenu)
		{
			EnableMenuItem(menu, FileMenu, MF_GRAYED);
			EnableMenuItem(menu, ChartMenu, MF_GRAYED);
			DrawMenuBar(hwnd);

			if (s_oglapp->GetApplicationWindow()->data.size != 0)
			{
				s_oglapp->GetApplicationWindow()->data.Destroy();
				RemoveMenu(menu, DataMenu, MF_BYCOMMAND);
			}

			FileOpen openfile(std::map < LPWSTR, LPWSTR > {{ L"CSV files", L"*.csv" }});
			if (openfile.ShowDialog())
			{
				s_oglapp->GetApplicationWindow()->data = CSVParser::Parse(openfile.getFile());

				popmenu = CreatePopupMenu();
				DataMenu = (UINT)popmenu;
				for (size_t i = 0; i < s_oglapp->GetApplicationWindow()->data.size; i++)
				{
					InsertMenuA(popmenu, i, MF_BYPOSITION, 9003, s_oglapp->GetApplicationWindow()->data[i].Name().c_str());
				}
			}
			AppendMenu(menu, MF_STRING | MF_POPUP, DataMenu, L"&Add DataSource");
			if (s_oglapp->GetApplicationWindow()->charts.size() == 0)
			{
				EnableMenuItem(menu, DataMenu, MF_GRAYED);
			}
			EnableMenuItem(menu, FileMenu, MF_ENABLED);
			EnableMenuItem(menu, ChartMenu, MF_ENABLED);
			DrawMenuBar(hwnd);
		}

		if (lparam == DataMenu)
		{
			s_oglapp->GetApplicationWindow()->charts[s_oglapp->GetApplicationWindow()->charts.size() - 1]->AddDataSource(s_oglapp->GetApplicationWindow()->data[wparam]);
		}

		if (lparam == ChartMenu)
		{
			EnableMenuItem(menu, EditMenu, MF_ENABLED);
			EnableMenuItem(menu, DataMenu, MF_ENABLED);
			switch (wparam)
			{
			case 0:
				s_oglapp->GetApplicationWindow()->charts.push_back(new OGLPieChart());
				break;
			case 1:
				s_oglapp->GetApplicationWindow()->charts.push_back(new OGLBarChart());
				break;
			case 2:
				s_oglapp->GetApplicationWindow()->charts.push_back(new OGLSpiderChart());
				break;
			case 3:
				s_oglapp->GetApplicationWindow()->charts.push_back(new OGLScatterPlot2D());
				break;
			case 4:
				s_oglapp->GetApplicationWindow()->charts.push_back(new OGLLineChart());
				break;
			case 5:
				s_oglapp->GetApplicationWindow()->charts.push_back(new OGLBoxChart());
				break;
			case 6:
				s_oglapp->GetApplicationWindow()->charts.push_back(new OGLScatterplot3D());
				break;
			case 7:
				s_oglapp->GetApplicationWindow()->charts.push_back(new OGLScatterplot3DV2());
				break;
			}
		}
		break;
	case WM_SIZE:
		s_oglapp->GetApplicationWindow()->Resize(LOWORD(lparam), HIWORD(lparam));
		break;
	case WM_CLOSE:
		s_oglapp->GetApplicationWindow()->RemoveCharts();
		s_oglapp->GetApplicationWindow()->DestroyOGLWindow();
		break;
	case WM_KEYDOWN:
		Listener::keys[wparam] = true;
		break;
	case WM_KEYUP:
		Listener::keys[wparam] = false;
		break;
	case WM_MOUSEMOVE:
		//inform the cursor position to OGLWindow
		s_oglapp->GetApplicationWindow()->MouseMove(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;
	case WM_MOUSEWHEEL:
		s_oglapp->GetApplicationWindow()->MouseWheel(HIWORD(wparam));
		break;
	case WM_LBUTTONUP:
		s_oglapp->GetApplicationWindow()->MouseLBUp(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;
	case WM_RBUTTONDOWN:
	{
		int x = GET_X_LPARAM(lparam) - (s_oglapp->GetApplicationWindow()->m_width >> 1);
		int y = -GET_Y_LPARAM(lparam) - -(s_oglapp->GetApplicationWindow()->m_height >> 1);
		if (s_oglapp->GetApplicationWindow()->charts.size() > 0)
		{
			std::tuple<bool, DataCell*, std::map<DataCell*, size_t>*> col = s_oglapp->GetApplicationWindow()->charts[s_oglapp->GetApplicationWindow()->charts.size() - 1]->MouseRB(x, y);

			if (std::get<0>(col))
			{
				if (std::get<1>(col) != nullptr && std::get<2>(col)->size() > 0)
				{
					InputBox(std::get<1>(col), std::get<2>(col));
					s_oglapp->GetApplicationWindow()->charts[s_oglapp->GetApplicationWindow()->charts.size() - 1]->InitElements();
				}

			}
		}

	}
		break;
	case WM_LBUTTONDOWN:
		s_oglapp->GetApplicationWindow()->MouseLBDown(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}
