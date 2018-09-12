// #include <stdio.h> // for C functions
#include <Windows.h> // for win32 functions



int main(int argc, char *argv[]) {
	// printf("Hello World %s\n", argv[2]);
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD written = 0;
	const char *str = "Hellsssso WorlD";
	int len = strlen(str);
	WriteFile(h, str, len, &written, NULL);


	return 0;
}
