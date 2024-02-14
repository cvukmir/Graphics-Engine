// Windows Header Files
#include <windows.h>
#include <SDKDDKVer.h> // Including SDKDDKVer.h defines the highest available Windows platform.
//#include <gdiplus.h>

#include "ArcColor.h"
#include "Arc2DLine.h"
#include "Arc2DPoint.h"

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
#define UNICODE
#define _UNICODE

//#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
//WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
//WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

const LPCWSTR WINDOW_CLASS = L"ArcEngineClass";
const LPCWSTR WINDOW_TITLE = L"ArcEngine";

int WIDTH = 0;
int HEIGHT = 0;

void* MEMORY;

bool IS_RUNNING = true;

BITMAPINFO BITMAP_INFO;

HWND WINDOW;

// Forward declarations of functions included in this code module:
ATOM             MyRegisterClass(HINSTANCE hInstance);
BOOL             InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void drawLine(Arc2DPoint startPoint, Arc2DPoint endPoint, ArcColor color);

// hInstance     - Instance of application.
// hPrevInstance - Not used, for 16-bit windows.
// lpCmdLine     - Command line arguments.
// nCmdShow      - Whether the window is starting maximized or minimized.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	RECT rect;
	GetClientRect(WINDOW, &rect);

	WIDTH  = rect.right  - rect.left;
	HEIGHT = rect.bottom - rect.top;

	MEMORY = VirtualAlloc(0, WIDTH * HEIGHT * (int)sizeof(UINT32), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	BITMAP_INFO.bmiHeader.biSize        = sizeof(BITMAP_INFO.bmiHeader);
	BITMAP_INFO.bmiHeader.biWidth       = WIDTH;
	BITMAP_INFO.bmiHeader.biHeight      = HEIGHT; // Make this negative to start at the bottom left,
	BITMAP_INFO.bmiHeader.biPlanes      = 1;
	BITMAP_INFO.bmiHeader.biBitCount    = 32;
	BITMAP_INFO.bmiHeader.biCompression = BI_RGB;

	UINT32* pixel = (UINT32*)MEMORY;

	HDC hdc = GetDC(WINDOW);

	// Clear the screen
	for (int i = 0; i < WIDTH * HEIGHT; ++i)
	{
		*(pixel++) = 0xFFFFFF;
	}

	Arc2DPoint startPoint(50, 50);
	Arc2DPoint endPoint(100, 100);

	drawLine(startPoint, endPoint, ArcColor());

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
			WIDTH,
			HEIGHT,
			0,
			0,
			WIDTH,
			HEIGHT,
			MEMORY,
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
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
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

void drawLine(const Arc2DPoint startPoint, const Arc2DPoint endPoint, ArcColor color)
{
	const int deltaX = endPoint.x() - startPoint.x();
	const int deltaY = endPoint.y() - startPoint.x();

	int x = startPoint.x();
	int y = startPoint.y();
	int p = (2 * deltaY) - deltaX;

	const int endX = endPoint.x();
	for (; x <= endX; ++x)
	{
		*((UINT32*)MEMORY + (sizeof(UINT32) * y) + x) = 0x0000FFFF;
		if (p > 0)
		{
			y++;
			p += (2 * deltaY) - (2 * deltaX);
		}
		else
		{
			p += 2 * deltaY;
		}
	}
}