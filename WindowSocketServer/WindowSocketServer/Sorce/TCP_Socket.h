#define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings

#pragma once
// ���� ���̺귯�� ��ũ �ɱ� �����θ� ���̳ʸ�ȭ ��Ų ������ Ȯ���� lib
#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "ws2_32.lib")

#include <mysql.h>
#include "Common.h"


class TCP_Socket
{
public:
	TCP_Socket();
	~TCP_Socket();

	// ���� �ʱ�ȭ ���� ���� 2.2 ����
	bool InitSocket();

	// ���� ����
	bool CreatSocket();

	// ���� ���ε�
	bool BindSocket(const char* _BindIP,int _BindPort);

	// ���� ���·� ����
	bool ListenSocket();

	// �������� Ŭ���̾�Ʈ ���� ����
	bool AcceptSocket();

	// Ŭ���̾�Ʈ���� ������ ����
	bool ConnectSocket(const char* _ServerIP, int _ConnectPort);
	
	// ������ ����
	bool SendSocket();

	// ������ ����
	bool ReciveSocket();
	
	// ����ü ����
	void SendStruct(SpawnActorInfo ActorInfo);

	// ����ü �ޱ�
	void ReciveStruct();


	SOCKET _Socket;

	SOCKET _SocketConnected;

	SOCKET _ServerSocket;
};

