#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
	//read
	FILE* fp = fopen("meat.jpg", "rb");

	//socket bind list accept fileread send
	fseek(fp, 0, SEEK_END);
	int Size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* Buffer = new char[Size+1];
	fread(Buffer, sizeof(char), Size, fp);
	fclose(fp);



	//윈속 초기화
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//소켓 생성
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	//서버 설정 
	SOCKADDR_IN ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = PF_INET;
	ServerAddr.sin_port = htons(1234);
	ServerAddr.sin_addr.s_addr = INADDR_ANY;

	//바인딩
	bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));

	//listen
	listen(ServerSocket, 0);

	while (1)
	{
		//새로 생기는 클라이언트 연결 정보
		SOCKADDR_IN ClientAddr;
		memset(&ClientAddr, 0, sizeof(ClientAddr));
		int ClientAddrLength = sizeof(ClientAddr);

		//accept
		SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &ClientAddrLength);

		//client에 전송
		send(ClientSocket, Buffer, Size, 0);

		closesocket(ClientSocket);
	}

	closesocket(ServerSocket);

	delete[] Buffer;
	WSACleanup();

	return 0;
}