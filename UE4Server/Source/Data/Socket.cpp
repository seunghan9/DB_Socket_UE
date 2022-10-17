#define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings

#include "Socket.h"

// ���� ���̺귯�� ��ũ �ɱ� �����θ� ���̳ʸ�ȭ ��Ų ������ Ȯ���� lib
#pragma comment (lib, "ws2_32.lib")

#include <string>
#include <string.h>
#include <iostream>

Socket::Socket()
{
	_Socket = INVALID_SOCKET;
	_SocketConnected = INVALID_SOCKET;
}

Socket::~Socket()
{
	// ������ �ݾ��ش�.
	closesocket(_Socket);
	closesocket(_SocketConnected);

	WSACleanup();
}


bool Socket::InitSocket()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		UE_LOG(LogTemp, Log, TEXT("Winsock Error : %s"), GetLastError());
		return false;
	}
	return true;
}


bool Socket::CreatSocket()
{
	_Socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_Socket == INVALID_SOCKET)
	{
		UE_LOG(LogTemp, Log, TEXT("Winsock Error : %s"), GetLastError());
		return false;
	}
	return true;
}

bool Socket::ConnectSocket(const char* _ServerIP, int _ConnectPort)
{
	SOCKADDR_IN ClinetSocketAddr;
	memset(&ClinetSocketAddr, 0, sizeof(SOCKADDR_IN));
	ClinetSocketAddr.sin_family = AF_INET;
	ClinetSocketAddr.sin_port = htons(_ConnectPort);
	ClinetSocketAddr.sin_addr.s_addr = inet_addr(_ServerIP);

	int Result = connect(_Socket, (SOCKADDR*)&ClinetSocketAddr, sizeof(SOCKADDR_IN));

	if (Result == SOCKET_ERROR)
	{
		UE_LOG(LogTemp, Log, TEXT("Winsock Error : %s"), GetLastError());
	}
	return true;
}

bool Socket::SendSocket()
{
	char	Buffer[] = "Bring Me The Thanos";
	int SendBytes = send(_Socket, Buffer, sizeof(Buffer), 0);
	FString MSG = Buffer;

	UE_LOG(LogTemp, Log, TEXT("Send MSG : % s"), *(MSG));

	if (SendBytes <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Winsock Error : %s"), GetLastError());
		return false;
	}
	return true;
}

bool Socket::ReciveSocket()
{
	char	Buffer[1024] = { 0, };
	int RecvBytes = recv(_Socket, Buffer, 1024, 0);
	FString MSG = Buffer;

	UE_LOG(LogTemp, Log, TEXT("Recive MSG : %s"), *(MSG));
	
	if (RecvBytes <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Winsock Error : %s"), GetLastError());
		return false;
	}
	return true;
}

void Socket::ReciveStruct(SpawnActorInfo* ActorInfo)
{
	int len;
	recv(_Socket, (char*)&len, sizeof(int), 0);

	char	Buffer[1024] = { 0, };
	recv(_Socket, Buffer, len, 0);

	ActorInfo = (SpawnActorInfo*)Buffer;

	UE_LOG(LogTemp, Log, TEXT("funtion : %i"), ActorInfo->Key);

}
