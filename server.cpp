#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
	//read
	FILE* fp = fopen("test.txt", "rb");

	//socket bind list accept fileread send
	fseek(fp, 0, SEEK_END);
	int Size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* Buffer = new char[Size+1];
	fread(Buffer, sizeof(char), Size, fp);
	fclose(fp);

	//socket connect recv filewrite
	//write
	FILE* ofp = fopen("test2.txt", "wb");
	fwrite(Buffer, sizeof(char), Size, ofp);
	fclose(ofp);

	cout << Buffer << endl;

	delete Buffer;

/*
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket;
	SOCKADDR_IN ServerAddr;

	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = PF_INET;
	ServerAddr.sin_port = htons(1234);
	ServerAddr.sin_addr.s_addr = INADDR_ANY;

	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));

	char Message[] = "what ary u doing now.";
	sendto(ServerSocket, Message, strlen(Message), 0, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));

	memset(&ClientAddr, 0, sizeof(ClientAddr));
	ClientAddr.sin_family = PF_INET;
	ClientAddr.sin_port = htons(1234);
	ClientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	char Buffer[1024] = { 0, };
	recvfrom(ServerSocket, Buffer, 1024, 0, (SOCKADDR*)&ClientAddr, &ClientAddrLength);

	cout << Buffer << endl;

	WSACleanup();
*/
	return 0;
}