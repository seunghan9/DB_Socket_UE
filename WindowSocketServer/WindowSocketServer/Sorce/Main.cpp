// ���� ���̺귯�� ��ũ �ɱ� �����θ� ���̳ʸ�ȭ ��Ų ������ Ȯ���� lib
#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "ws2_32.lib")

#include <mysql.h>
#include <stdio.h>
// ���� ���̺귯�� ��ũ �ɱ�
#include <iostream>
#include "TCP_Socket.h"
#include "MySQL.h"


using namespace std;

#define PORT	4000
#define PACKED_SIZE 1024
#define MyIP "127.0.0.1"

int main()
{


	MySQL* sql = new MySQL;

	sql->ConncetMySQL();

	sql->RecQueryResult();

	sql->OutResult();

	TCP_Socket* Socket = new TCP_Socket;

	Socket->InitSocket();
	
	Socket->CreatSocket();
	
	Socket->BindSocket(MyIP, 4000);
	
	Socket->ListenSocket();
	
	Socket->AcceptSocket();

	Socket->SendSocket();

	Socket->ReciveSocket();

	mysql_free_result(sql->mysqlResult);

	delete Socket;
	delete sql;

	return 0;
}