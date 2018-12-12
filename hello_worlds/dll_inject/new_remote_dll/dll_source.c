#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

#include <stdio.h>

LRESULT CALLBACK myWindowProc(_In_ HWND   hwnd, _In_ UINT   uMsg, 
							  _In_ WPARAM wParam, _In_ LPARAM lParam) {
	if (uMsg == WM_CLOSE) {
		MessageBoxA(NULL, "Hello", "Close", MB_OK);
		//MoveWindow(hwnd, 100, 100, 200, 200, TRUE);
		//return 0;
		exit(0);
	}

	return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

LONG_PTR previous;

FILE* text_file = NULL;

LRESULT CALLBACK myEditWindowProc(_In_ HWND   hwnd, _In_ UINT   uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	if (uMsg == WM_CHAR) {
		if (text_file == NULL) {
			text_file = fopen("C:\\shy\\lessons\\hello_worlds\\dll_inject\\my_text.txt", "r");
		}
		
		wParam = fgetc(text_file);

		//MessageBoxA(NULL, "Hello", "Close", MB_OK);
		//MoveWindow(hwnd, 100, 100, 200, 200, TRUE);
		//return 0;
		//exit(0);
	}

	return CallWindowProcA(previous, hwnd, uMsg, wParam, lParam);

	//return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}




BOOL CALLBACK myEnumWindowsProc(_In_ HWND   hwnd, _In_ LPARAM lParam) {
	HWND* theHwndLookingFor = (HWND*)lParam;

	DWORD thisId = 0;
	GetWindowThreadProcessId(hwnd, &thisId);
	if (thisId == GetCurrentProcessId()) {
		*theHwndLookingFor = hwnd;
		return FALSE;
	}
	return TRUE; // continue iteration
}

void hijack_window() {
	HWND notepadHwnd = FindWindowExA(NULL, NULL, "Notepad", NULL);
	HWND editWnd = FindWindowExA(notepadHwnd, NULL, "Edit", NULL);

	//HWND theHwndLookingFor = 0;
	//EnumWindows(myEnumWindowsProc, &theHwndLookingFor);

	previous = GetWindowLongPtrA(editWnd, GWLP_WNDPROC);

	// THIS DOESN'T WORK!
	//SetWindowLongPtrA(theHwndLookingFor, GWLP_WNDPROC, previous);
	SetWindowLongPtrA(editWnd, GWLP_WNDPROC, (LONG_PTR)myEditWindowProc);

}
BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
) 
{
	if (fdwReason == DLL_PROCESS_ATTACH) {
		hijack_window();
		//MessageBoxW(NULL, L"ωμεν", L"dll", MB_OK);
	}

	return TRUE;
}