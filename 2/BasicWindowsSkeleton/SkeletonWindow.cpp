#include "Precompiled.h"

//#include <windows.h>    // include the basic windows header file


typedef LRESULT(*message_callback)(HWND, WPARAM, LPARAM);

struct message_handler
{
	UINT message;
	message_callback handler;
};
 
static message_handler s_handlers[] = {
	{
		WM_PAINT, [](HWND window, WPARAM, LPARAM) -> LRESULT
		{
			PAINTSTRUCT ps;
			VERIFY(BeginPaint(window, &ps));
			TRACE(L"Paint!\n");

			EndPaint(window, &ps);
			return 0;
		}
	},
	{
		WM_DESTROY, [](HWND, WPARAM, LPARAM) -> LRESULT
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	

};

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE module,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	WNDCLASS wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hInstance = module;
	wc.lpszClassName = L"windows";
	wc.lpfnWndProc = [](HWND window, UINT message, WPARAM wparam, LPARAM lparam) -> LRESULT
	{
		for (auto h = s_handlers; h != s_handlers + _countof(s_handlers); ++h){
			if (message == h->message){
				return h->handler(window, wparam, lparam);
			}
		}

		return DefWindowProc(window, message, wparam, lparam);
	};

	VERIFY(RegisterClass(&wc));

	auto hwnd = CreateWindow(wc.lpszClassName, L"title", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, module, nullptr);

	ASSERT(hwnd);

	MSG message;
	BOOL result;
	 
	while (result = GetMessage(&message, 0, 0, 0)){
		if (-1 != result){
			DispatchMessage(&message);

		}
	}

}
