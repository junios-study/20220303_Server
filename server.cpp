#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#include <string>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
	//���� �ʱ�ȭ
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//���� ����
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	//���� ���� 
	SOCKADDR_IN ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = PF_INET;
	ServerAddr.sin_port = htons(1234);
	ServerAddr.sin_addr.s_addr = INADDR_ANY;

	//���ε�
	bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));

	//listen
	listen(ServerSocket, 0);

	while (1)
	{
		//���� ����� Ŭ���̾�Ʈ ���� ����
		SOCKADDR_IN ClientAddr;
		memset(&ClientAddr, 0, sizeof(ClientAddr));
		int ClientAddrLength = sizeof(ClientAddr);

		//accept
		SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &ClientAddrLength);

		//Ŭ���̾�Ʈ�� ��� ����
		char Buffer[2049] = { 0, };
		memset(Buffer, 0, sizeof(Buffer));
		string Packet;
		int recvLength = recv(ClientSocket, Buffer, 2048, 0);

		if (recvLength < 0)
		{
			cout << "error : " << GetLastError() << endl;
			closesocket(ClientSocket);
			break;
		}

		Packet = Buffer;
		//get filename
		string Command = Packet.substr(0, 3);
		string Filename = Packet.substr(4, Packet.length() - 4);

		//read
		FILE* fp = fopen(Filename.c_str(), "rb");

		size_t readDataLength = fread(Buffer, sizeof(char), 2048, fp);
		while (readDataLength != 0)
		{
			send(ClientSocket, Buffer, readDataLength, 0);
			readDataLength = fread(Buffer, sizeof(char), 2048, fp);
		}
		fclose(fp);

		//client�� ����

		closesocket(ClientSocket);
	}

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}