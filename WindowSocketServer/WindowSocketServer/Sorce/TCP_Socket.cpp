// ���� ���̺귯�� ��ũ �ɱ� �����θ� ���̳ʸ�ȭ ��Ų ������ Ȯ���� lib
#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "ws2_32.lib")

#include <mysql.h>
#include <string.h>
#include "TCP_Socket.h"
#include <iostream>


TCP_Socket::TCP_Socket()
{
	_Socket = INVALID_SOCKET;
	_SocketConnected = INVALID_SOCKET;
}

TCP_Socket::~TCP_Socket()
{
	// ������ �ݾ��ش�.
	closesocket(_Socket);
	closesocket(_SocketConnected);

	WSACleanup();
}


bool TCP_Socket::InitSocket()
{
	// WSADATA windows ���� �ʱ�ȭ ������ �����ϱ� ���� ����ü
	WSADATA wsaData;

	// ������� ��� ������ Ȱ���� ������ ����
	// ù ���ڴ� WORD�� unsigned Short Typedef �̴�.
	// ���� ���� 2.2 ������ �Ǽ� ������ MAKE WORD�� ����Ͽ� ������ �־��ش�.
	// �� ��° ���ڴ� WSADATA�� ������ Ÿ��
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		std::cout << " Winsock Error: " << GetLastError() << std::endl; // ������ ���� ���� Ȯ��
		exit(-1);
		return false;
	}
	return true;
}


bool TCP_Socket::CreatSocket()
{
	// ������ �ڵ��̴�. �ڵ��̶� �ü���� �����ϴ� Ŀ�� ������Ʈ �� �� �����̴�.
	// OS�� �ڵ��� �̿��Ͽ� ���α׷��� �������� �����Ѵ�.

	// TCP ������ ũ�� 2������ ������.
	// ù ��° �ٸ� ��ǻ�ͷ� ���� ������ ���� ���� ��û�� �������ִ� ����
	// �� ��°�� �ٸ� ��ǻ�Ϳ� ����� ������ �־���Ѵ�.

	// ��ǻ�ʹ� IP�ּҶ�� ������ �̿��Ͽ� �ش� ��ǻ���� �ּ������� ������.
	// IP �ּҴ� ũ�� 2������ ������. IPV4 IPV6
	// IPV4 Ÿ���� 32bit �� 4byte�� Ȱ���Ѵ�. �Ϲ������� ����ϴ� IP�ּ��̴�.
	// IPV4�� ǥ�� �Ѱ�� ���� IPV6 Ÿ�� 16byte �ּ� ü�踦 ����� �Ǿ��´�.

	// PF_INET�� IPV4 Ÿ���� ������̰�, SOCK_STREAM�� ���븦 ����� ���� ������ ������ ����ڴٴ� �ǹ��̴�.
	// ������ ���ڴ� protocol �� ��� �Ծ��� ����. TCP�� ��������� IPPROTOCOL_TCP�� ����Ѵٰ� �����Ѵ�.
	_Socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_Socket == INVALID_SOCKET)
	{
		std::cout << " fail create Socket : " << GetLastError() << std::endl; // ������ ���� ���� Ȯ��
		exit(-1);
		return false;
	}
	return true;
}


bool TCP_Socket::BindSocket(const char* _BindIP, int _BindPort)
{
	// ������ ������Ҹ� ���� ����ü ���� �� �� �Ҵ�
	// �ּҸ� �����ϴ� ���� IP �� PORT 2������ �����ȴ�.
	// IP�� �ּ� PORT�� �����̴�. ��Ʈ�� ��Ȯ�ϰ� �����ؾ��Ѵ�.

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN));

	// family�� ������ ������ ���� �Ǵ� ���� �ּҸ� �����ϴ� �� ���ȴ�.
	// �ּ� ������ ��Ƶδ� ����ü�̴�.
	// �޸𸮿� �����͸� ������ ���� 2���� ����� �ִµ�, �򿣵�Ȱ� ��Ʋ������̶� ����̴�.
	// �򿣵���� ��Ʈ��ũ�� ǥ�� ��������, ��Ʋ������� �ַ� ���� ���μ��� �迭�̴�.
	// Ȥ���� �ٸ� ����� ����ϴ� ��ǻ�Ͱ� �����͸� �ְ� �ް� �� ��� ������ �߻��� �� ������ ��Ʈ��ũ ǥ���� ����Ѵ�.
	// AF_INET�� UDP TCP�� ���������� �����̸� �ݵ�� AF_INET�̾�� ���� �� �� �ִ�.
	ServerSockAddr.sin_family = AF_INET;


	// ������ ���� ��ǻ���� IP�ּҸ� �־���Ѵ�.
	// s_addr�� IPv4 internet address�̴�.
	ServerSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// ��Ʈ ��ȣ�� �����Ѵ�. ��Ʈ�� 2����Ʈ �ȿ��� ǥ���� �� �ִ� ���ڿ����Ѵ�.
	// htons host to networkshort �� �򿣵�� ������� �����͸� ��ȯ�Ͽ� �����Ѵ�.
	ServerSockAddr.sin_port = htons(_BindPort);

	// ���ε� �Լ��� ���Ͽ� �ּ� ������ �����Ѵ�.
	// ���� ������ ������ ���ӽ��θ��� ���ش�.
	// ù ���ڷδ� ������ ������ 2��° ���ڴ� �ּ������� ����° ���ڴ� �ι�° ���ڷ� ���� ����ü�� ũ�Ⱑ ����.
	int Result = bind(_Socket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));

	if (Result == SOCKET_ERROR)
	{
		std::cout << " fail bind : " << GetLastError() << std::endl; // ������ ���� ���� Ȯ��
		exit(-1);
		return false;
	}

	return true;
}


bool TCP_Socket::ListenSocket()
{
	// listen �Լ��� ������ �����ϴ� ���·� ������ ���¸� �������ش�.
	// ���� ������ ��ٸ��� ���°� �Ǵ� ���̴�.
	// 2��° ���ڴ� �Ѳ����� ��û ������ �ִ� ���� ���� ���� ���Ѵ�.
	int Result = listen(_Socket, SOMAXCONN);

	if (Result == SOCKET_ERROR)
	{
		std::cout << " fail listen : " << GetLastError() << std::endl; // ������ ���� ���� Ȯ��
		exit(-1);
		return false;
	}
	return true;
}

bool TCP_Socket::AcceptSocket()
{
	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(SOCKADDR_IN));
	int ClientSockAddrLength = sizeof(ClientSockAddr);

	// accept �Լ��� �̿��Ͽ� ���� ��û�� �����Ѵ�. �� �Լ��� ����ȭ�� ������� �����Ѵ�.
	// ����ȭ�� ����̶� ��û�� �������ϱ� �������� ��� ��� ���¿� ���̴� ���� ���Ѵ�.
	// �� ��û�� ������������ �� �Լ��� �Ⱥ������´�.
	// ���� ��û�� �����ϸ� ����� ������ ��������� ���ϵȴ�.
	// ù ���ڷδ� ���� �ι�° ���ڷδ� ���ε� ������ �ּ� ����°�� ����ü�� ũ�Ⱑ ����.

	_SocketConnected = accept(_Socket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);

	if (_SocketConnected == SOCKET_ERROR)
	{
		std::cout << " fail accept : " << GetLastError() << std::endl; // ������ ���� ���� Ȯ��
		exit(-1);
		return false;
	}
	
	return true;
}

bool TCP_Socket::ConnectSocket(const char* _ServerIP, int _ConnectPort)
{
	_ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_Socket == INVALID_SOCKET)
	{
		std::cout << " fail create Socket : " << GetLastError() << std::endl; // ������ ���� ���� Ȯ��
		exit(-1);
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
		std::cout << " fail connect : " << GetLastError() << std::endl; // ������ ���� ���� Ȯ��
		exit(-1);
	}
	return true;
}

bool TCP_Socket::SendSocket()
{
	char	Buffer[] = "Bring Me The Thanos";

	int SendBytes = send(_SocketConnected, Buffer, sizeof(Buffer), 0);

	if (SendBytes <= 0)
	{
		std::cout << " fail recv : " << GetLastError() << std::endl; // ������ ���� ���� Ȯ��
		exit(-1);
		return false;
	}
	return true;
}

bool TCP_Socket::ReciveSocket()
{
	// Ŭ���̾�Ʈ�� ������ �����ϱ� ���� ������ �����ص� ��Ŷ ũ�⸸ŭ ���۸� �����Ѵ�.
	// recv(����, ���� ������ ���� �迭 �ּ�, �迭�� ũ��, flag)
	// recv �Լ��� ��� �������κ��� ������ ������ �޾��ִ� ������ �Ѵ�.
	// ������ �����Ͱ� ���ٸ� ���⼭ ���� ������ ��� �����·� �ִ´�.
	// flag �����δ� Ȱ������ �������� 0�� �Ѵ�.
	char	Buffer[1024] = {0,};
	int RecvBytes = recv(_SocketConnected, Buffer, 1024, 0);

	std::cout << "Recive Message : " << Buffer << std::endl;

	if (RecvBytes <= 0)
	{
		std::cout << " fail send : " << GetLastError() << std::endl; // ������ ���� ���� Ȯ��
		exit(-1);
		return false;
	}
	return true;
}

void TCP_Socket::SendStruct(SpawnActorInfo ActorInfo)
{
	int SendInt;
	int SendIntLength = sizeof(ActorInfo);
	SendInt = send(_SocketConnected, (char*)&SendIntLength, sizeof(int), 0);
	if (SendInt == SOCKET_ERROR)
	{
		std::cout << "Send Error" << std::endl;
		exit(-1);
	}
	SendInt = send(_SocketConnected, (char*)&ActorInfo, sizeof(SpawnActorInfo), 0);
	if (SendInt == SOCKET_ERROR)
	{
		std::cout << "Send Error" << std::endl;
		exit(-1);
	}
}

void TCP_Socket::ReciveStruct()
{
}

