#define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings

#include "Socket.h"

// 소켓 라이브러리 링크 걸기 구현부를 바이너리화 시킨 파일의 확장자 lib
#pragma comment (lib, "ws2_32.lib")

#include <string.h>
#include <iostream>

Socket::Socket()
{
	_Socket = INVALID_SOCKET;
	_SocketConnected = INVALID_SOCKET;
}

Socket::~Socket()
{
	// 소켓을 닫아준다.
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


bool Socket::BindSocket(const char* _BindIP, int _BindPort)
{
	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerSockAddr.sin_port = htons(_BindPort);
	int Result = bind(_Socket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));

	if (Result == SOCKET_ERROR)
	{
		UE_LOG(LogTemp, Log, TEXT("Winsock Error : %s"), GetLastError());
		return false;
	}

	return true;
}


bool Socket::ListenSocket()
{
	int Result = listen(_Socket, SOMAXCONN);

	if (Result == SOCKET_ERROR)
	{
		UE_LOG(LogTemp, Log, TEXT("Winsock Error : %s"), GetLastError());
		return false;
	}
	return true;
}

bool Socket::AcceptSocket()
{
	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(SOCKADDR_IN));
	int ClientSockAddrLength = sizeof(ClientSockAddr);

	_SocketConnected = accept(_Socket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);

	if (_SocketConnected == SOCKET_ERROR)
	{
		UE_LOG(LogTemp, Log, TEXT("Winsock Error : %s"), GetLastError());
		return false;
	}

	return true;
}

bool Socket::ConnectSocket(const char* _ServerIP, int _ConnectPort)
{
	_ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_Socket == INVALID_SOCKET)
	{
		UE_LOG(LogTemp, Log, TEXT("Winsock Error : %s"), GetLastError());
		return false;
	}

	SOCKADDR_IN ClinetSocketAddr;
	memset(&ClinetSocketAddr, 0, sizeof(SOCKADDR_IN));
	ClinetSocketAddr.sin_family = AF_INET;
	ClinetSocketAddr.sin_port = htons(_ConnectPort);
	ClinetSocketAddr.sin_addr.s_addr = inet_addr(_ServerIP);

	int Result = connect(_ServerSocket, (SOCKADDR*)&ClinetSocketAddr, sizeof(SOCKADDR_IN));

	if (Result == SOCKET_ERROR)
	{
		UE_LOG(LogTemp, Log, TEXT("Winsock Error : %s"), GetLastError());
	}
	return true;
}

bool Socket::SendSocket()
{
	char	Buffer[] = "Bring Me The Thanos";

	int SendBytes = send(_SocketConnected, Buffer, sizeof(Buffer), 0);

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
	int RecvBytes = recv(_SocketConnected, Buffer, 1024, 0);

	std::cout << "Recive Message : " << Buffer << std::endl;

	if (RecvBytes <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Winsock Error : %s"), GetLastError());
		return false;
	}
	return true;
}
