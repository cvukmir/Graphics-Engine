// Windows Header Files
#include <windows.h>
#include <SDKDDKVer.h> // Including SDKDDKVer.h defines the highest available Windows platform.
//#include <gdiplus.h>
#include <comdef.h>

#include "ArcConstants.h"
#include "ArcColor.h"
#include "Arc2DLine.h"
#include "Arc2DPoint.h"
#include "ArcWindow.h"
#include "ArcPnmParser.h"
#include "ArcEnums.h"
#include "ArcRdParser.h"

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
#define UNICODE
#define _UNICODE

//#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
//WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
//WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//ArcWindow* ArcWindow::_pInstancePtr = nullptr;

bool IS_RUNNING = true;

BITMAPINFO BITMAP_INFO;

HWND WINDOW;

ArcWindow* ArcWindow::_pInstancePtr = nullptr;
ArcWindow* ARC_WINDOW = nullptr;

const int INITIAL_WIDTH = 1920;
const int INITIAL_HEIGHT = 1080;


// Forward declarations of functions included in this code module:
ATOM             MyRegisterClass(HINSTANCE hInstance);
BOOL             InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



// hInstance     - Instance of application.
// hPrevInstance - Not used, for 16-bit windows.
// lpCmdLine     - Command line arguments.
// nCmdShow      - Whether the window is starting maximized or minimized.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);

	if (lpCmdLine[0] == NULL)
	{
		return 0;
	}

	std::string fileName = std::string(_bstr_t(lpCmdLine[0]));
	if (!fileName.ends_with(".rd"))
	{
		return 0;
	}

	ArcRdParser rd;
	if (!rd.openFile(fileName))
	{
		return 0;
	}

	ARC_WINDOW = ArcWindow::window();

	if (rd.displayType() == ArcRdDisplayType::Pnm)
	{
		ArcPnmParser::writeToPnmFile("test.pnm");

		return 0;
	}

//	GetWindowRect(test, rect1);

	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	RECT rect;
	GetClientRect(WINDOW, &rect);

	ARC_WINDOW->windowWidth( rect.right - rect.left);
	ARC_WINDOW->windowHeight(rect.bottom - rect.top);

	ARC_WINDOW->initializeMemory();

	BITMAP_INFO.bmiHeader.biSize        = sizeof(BITMAP_INFO.bmiHeader);
	BITMAP_INFO.bmiHeader.biWidth       = ARC_WINDOW->windowWidth();
	BITMAP_INFO.bmiHeader.biHeight      = -ARC_WINDOW->windowHeight(); // Make this negative to start at the bottom left,
	BITMAP_INFO.bmiHeader.biPlanes      = 1;
	BITMAP_INFO.bmiHeader.biBitCount    = 32;
	BITMAP_INFO.bmiHeader.biCompression = BI_RGB;

	HDC hdc = GetDC(WINDOW);

	Arc2DPoint startPoint(50, 100);
	Arc2DPoint endPoint(100, 100);

	Arc2DPoint circlePoint(150, 150);

	ARC_WINDOW->drawLine(startPoint, endPoint, ArcColor(ArcColor::GREEN));

	ARC_WINDOW->drawLine(Arc2DPoint(100, 100), Arc2DPoint(50, 100), ArcColor(ArcColor::BLUE));

	ARC_WINDOW->drawCircle(circlePoint, 50, ArcColor(ArcColor::MAGENTA));


	// Main message loop:
	MSG msg;
	while (IS_RUNNING)
	{
		while (PeekMessage(&msg, WINDOW, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		StretchDIBits(
			hdc,
			0,
			0,
			ARC_WINDOW->windowWidth(),
			ARC_WINDOW->windowHeight(),
			0,
			0,
			ARC_WINDOW->windowWidth(),
			ARC_WINDOW->windowHeight(),
			ARC_WINDOW->memory(),
			&BITMAP_INFO,
			DIB_RGB_COLORS,
			SRCCOPY);
	}

	return 0;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex = {0};

	wcex.cbSize        = sizeof(WNDCLASSEX);
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WndProc;
	wcex.hInstance     = hInstance;
	wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
	wcex.lpszClassName = WINDOW_CLASS;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	WINDOW = CreateWindowW(
		WINDOW_CLASS,
		WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		256,
		256,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if (!WINDOW)
	{
		return FALSE;
	}

	ShowWindow(WINDOW, nCmdShow);
	UpdateWindow(WINDOW);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
//		case WM_PAINT:
//			PAINTSTRUCT ps;
//			HDC hdc = BeginPaint(hWnd, &ps);
//			// TODO: Add any drawing code that uses hdc here...
//			EndPaint(hWnd, &ps);
//			break;
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			IS_RUNNING = false;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}