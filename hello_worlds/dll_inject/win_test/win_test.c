
#include <Windows.h> // for win32 functions
#include <stdio.h>


LRESULT CALLBACK myWindowProc(_In_ HWND   hwnd, _In_ UINT   uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	if (uMsg == WM_CLOSE) {
		MessageBoxA(NULL, "Hello", "Close", MB_OK);
		//MoveWindow(hwnd, 100, 100, 200, 200, TRUE);
		//return 0;
		exit(0);
	}
	if (uMsg == WM_PAINT) {

	}
	
	return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

int main() {
	HWND h = FindWindowExA(NULL, NULL, "Notepad", NULL);

}


int main_x(int argc, char *argv[]) {
	HWND hwnd = CreateWindowA("Static", "bla",
		WS_BORDER | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 100, 100, NULL, NULL, NULL, NULL);

	SetWindowLongPtrA(hwnd, GWLP_WNDPROC, (LONG)myWindowProc);

	//Sleep(10000);
	MSG msg;
	BOOL bRet;

	while (1)
	{
		bRet = GetMessage(&msg, NULL, 0, 0);

		if (bRet > 0)  // (bRet > 0 indicates a message that must be processed.)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (bRet < 0)  // (bRet == -1 indicates an error.)
		{
			// Handle or log the error; possibly exit.
			// ...
		}
		else  // (bRet == 0 indicates "exit program".)
		{
			break;
		}
	}
	return msg.wParam;

	//return 0;
}
