#include <windows.h>


LRESULT CALLBACK myWindowProc(_In_ HWND   hwnd, _In_ UINT   uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	if (uMsg == WM_CLOSE) {
		MessageBoxA(NULL, "Hello", "Close", MB_OK);
		//MoveWindow(hwnd, 100, 100, 200, 200, TRUE);
		//return 0;
		exit(0);
	}

	return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

HWND theHwndLookingFor = 0;
BOOL CALLBACK myEnumWindowsProc(_In_ HWND   hwnd, _In_ LPARAM lParam) {
	DWORD thisId = 0;
	GetWindowThreadProcessId(hwnd, &thisId);
	if (thisId == GetCurrentProcessId()) {
		theHwndLookingFor = hwnd;
		return FALSE;
	}
	return TRUE; // continue iteration
}

void hijack_window() {
	HWND hwnd = FindWindowExA(NULL, NULL, "Notepad", NULL);

	EnumWindows(myEnumWindowsProc, 0);

	//LONG x = (LONG)myWindowProc;
	LONG_PTR previous = GetWindowLongPtrA(theHwndLookingFor, GWLP_WNDPROC);

	// THIS DOESN'T WORK!
	SetWindowLongPtrA(theHwndLookingFor, GWLP_WNDPROC, previous);
	//SetWindowLongPtrA(theHwndLookingFor, GWLP_WNDPROC, (LONG_PTR)myWindowProc);


}

BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
) 
{
	if (fdwReason == DLL_PROCESS_ATTACH) {
		hijack_window();
		//MessageBoxW(NULL, L"ωμεν", "dll", MB_OK);
	}


}