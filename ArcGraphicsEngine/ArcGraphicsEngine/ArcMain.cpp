// Windows
#include <comdef.h>
#include <SDKDDKVer.h> // Including SDKDDKVer.h defines the highest available Windows platform.
#include <windows.h>

// ArcWindow
#include "ArcWindow.h"

// ArcIO
#include "ArcPnmParser.h"
#include "ArcRdParser.h"

#include <iostream>

//#include <ArcLogger.h>
//#include <ArcLoggingMacros.h>

// ArcFramework
#include "ArcEnums.h"

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers

// Global Variables:
HINSTANCE  hInst;       // Current instance
BITMAPINFO BITMAP_INFO; // Bitmap
HWND       WINDOW;      // Window

ArcWindow* ArcWindow::_pInstancePtr = nullptr; // Initialize the singularity.
ArcWindow*               ARC_WINDOW = nullptr; // One and only global instance of the window.
//ArcLogger*               ARC_LOGGER = nullptr; // One and only global instance of the logger.


// Forward declarations of functions included in this code module:
ATOM             MyRegisterClass(HINSTANCE hInstance);
BOOL             InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void             CreateBitmap();

// hInstance     - Instance of application.
// hPrevInstance - Not used, for 16-bit windows.
// lpCmdLine     - Command line arguments.
// nCmdShow      - Whether the window is starting maximized or minimized.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);

	//ARC_LOGGER = ArcLogger::logger();
	//ARC_LOG("Program Starting...");

	// Ensure there is a command line argument given.
	if (lpCmdLine[0] == NULL)
	{
		//ARC_LOG("No file name was passed through the command line arguments.\n");
		return -1;
	}

	std::string fileName = std::string(_bstr_t(lpCmdLine));
	//ARC_LOG("Reading file " + fileName + ".\n");


	// Open the .rd file.
	ArcRdParser renderer;
	if (!renderer.openAndReadFile(fileName))
	{
		//ARC_LOG("Error reading " + fileName + ".\n");
		return -1;
	}

	// Initialize the window based on the header of the .rd file.
	ARC_WINDOW = ArcWindow::window();

	ARC_WINDOW->windowWidth(renderer.width());
	ARC_WINDOW->windowHeight(renderer.height());

	renderer.executeCommands(ARC_WINDOW);
	
	// Check if displaying to screen or a pnm file.
	if (renderer.displayType() == ArcRdDisplayType::Pnm)
	{
		return ArcPnmParser::writeToPnmFile(renderer.displayName() + ".pnm");
	}

	// Creating a window to display the image.
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return -1;
	}

	// Create a bitmap to map memory to the screen window.
	CreateBitmap();

	HDC hdc = GetDC(WINDOW);

	// Display the frame to the screen.
	RedrawWindow(WINDOW, 0, 0, RDW_INVALIDATE | RDW_UPDATENOW);

	// Main message loop:
	MSG msg;
	while (ARC_WINDOW->isRunning())
	{
		// Execute each message.
		while (PeekMessage(&msg, WINDOW, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	delete(ARC_WINDOW);
	//delete(ARC_LOGGER);

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
		WS_POPUP | WS_VISIBLE | WS_SYSMENU,
		0,
		0,
		ARC_WINDOW->windowWidth(),
		ARC_WINDOW->windowHeight(),
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
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			for (ArcFrameList::const_iterator it = ARC_WINDOW->frameBegin(); it != ARC_WINDOW->frameEnd(); ++it)
			{
				// Display the frame to the screen.
				StretchDIBits(
					GetDC(WINDOW),
					0,
					0,
					ARC_WINDOW->windowWidth(),
					ARC_WINDOW->windowHeight(),
					0,
					0,
					ARC_WINDOW->windowWidth(),
					ARC_WINDOW->windowHeight(),
					(*it),
					&BITMAP_INFO,
					DIB_RGB_COLORS,
					SRCCOPY);
			}

			EndPaint(hWnd, &ps);
			break;
		case WM_KEYDOWN:
			if (wParam == VK_F2)
			{
				RedrawWindow(hWnd, 0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			break;
		case WM_LBUTTONDOWN:
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			ARC_WINDOW->isRunning(false);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void CreateBitmap()
{
	BITMAP_INFO.bmiHeader.biSize        = sizeof(BITMAP_INFO.bmiHeader);
	BITMAP_INFO.bmiHeader.biWidth       = ARC_WINDOW->windowWidth();
	BITMAP_INFO.bmiHeader.biHeight      = -ARC_WINDOW->windowHeight(); // Make this negative to start at the bottom left,
	BITMAP_INFO.bmiHeader.biPlanes      = 1;
	BITMAP_INFO.bmiHeader.biBitCount    = 32;
	BITMAP_INFO.bmiHeader.biCompression = BI_RGB;
}