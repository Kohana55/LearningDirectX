#include <Windows.h>
#include <string>


// A callback to our custom Windows Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	case WM_CLOSE:
		PostQuitMessage(1337);
		break;
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	case WM_CHAR:
	{
		static std::string title;
		title.push_back(wParam);
		SetWindowText(hWnd, title.c_str());
	}
	break;
	case WM_LBUTTONDOWN:
	{
		POINTS points = MAKEPOINTS(lParam);
		char mousePos[100];
		sprintf_s(mousePos, "X:%d Y:%d", points.x, points.y);
		SetWindowText(hWnd, mousePos);
	}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Entry Point (main)
int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	// Setup WNDCLASSEX (descriptor)
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "LewisDX";
	wc.hIconSm = NULL;

	// Reigster WNDCLASSEX
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowEx(0, "LewisDX", "LewisDXWindow", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);


	// Setup windows messaging (Message pump)
	MSG msg;
	BOOL result;
	while (result = GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	// Handle exiting of window
	if (result == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
}