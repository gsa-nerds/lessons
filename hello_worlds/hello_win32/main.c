
#include <Windows.h> // for win32 functions



int main(int argc, char *argv[]) {

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD written = 0;
	const char *str = "Hellsssso WorlD";
	int len = strlen(str);
	WriteFile(h, str, len, &written, NULL);


	return 0;
}
