// ���� ���̺귯�� ��ũ �ɱ� �����θ� ���̳ʸ�ȭ ��Ų ������ Ȯ���� lib
#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "ws2_32.lib")

#include <mysql.h>
#include <stdio.h>
// ���� ���̺귯�� ��ũ �ɱ�
#include <iostream>




using namespace std;

#define PORT	4000
#define PACKED_SIZE 1024

int main()
{

	// MySQL ������ ���� ����ü
	MYSQL conn;				

	// MySQL �ڵ�
	MYSQL* ConnPtr = NULL;	
	
	// ���� ������ ����� ��� ����ü ������
	MYSQL_RES* mysqlResult;
	
	// ���� ������ ����� ���� ���� ������ ��� ����ü
	MYSQL_ROW Row;			
	
	// ���� ��û �� ��� (����, ����)
	int Stat;				

	// MySQL ���� �ʱ�ȭ
	mysql_init(&conn);		

	// ������ ���̽��� ����
	ConnPtr = mysql_real_connect(&conn, "localhost", "root", "Mytmdgh0910!", "seung0910", 3306, NULL, 0);

	// ���� ��� Ȯ�� Null�� ��� ����
	if (ConnPtr == NULL)
	{
		std::cout << stderr << "Mysql Connection Error : " << mysql_error(&conn);
		return 1;
	}


	// ���� ��û (���̺� �˻�)
	const char* Query = "SELECT * FROM seunghan9";
	Stat = mysql_query(ConnPtr, Query);
	if (Stat != 0)
	{
		std::cout << stderr << "Mysql Connection Error : " << mysql_error(&conn);
		return 1;
	}

	// ��û ��� ����
	mysqlResult = mysql_store_result(ConnPtr);


	// ��û ��� ���
	while ((Row = mysql_fetch_row(mysqlResult)) != NULL)
	{
		for (int i = 0; i < mysql_num_fields(mysqlResult); ++i)
		{
			cout << Row[i] << "  ";
		}
		cout << endl;
	}

	// Query ��� �ʱ�ȭ
	mysql_free_result(mysqlResult);

	// Database ����
	mysql_close(ConnPtr);

	// WSADATA windows ���� �ʱ�ȭ ������ �����ϱ� ���� ����ü
	WSADATA wsaData;

	// ������� ��� ������ Ȱ���� ������ ����
	// ù ���ڴ� WORD�� unsigned Short Typedef �̴�.
	// ���� ���� 2.2 ������ �Ǽ� ������ MAKE WORD�� ����Ͽ� ������ �־��ش�.
	// �� ��° ���ڴ� WSADATA�� ������ Ÿ��
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << " Winsock Error: " << GetLastError() << endl; // ������ ���� ���� Ȯ��
		exit(-1);
	}

	// ������ �ڵ��̴�. �ڵ��̶� �ü���� �����ϴ� Ŀ�� ������Ʈ �� �� �����̴�.
	// OS�� �ڵ��� �̿��Ͽ� ���α׷��� �������� �����Ѵ�.
	
	// TCP ������ ũ�� 2������ ������.
	// ù ��° �ٸ� ��ǻ�ͷ� ���� ������ ���� ���� ��û�� �������ִ� ����
	// �� ��°�� �ٸ� ��ǻ�Ϳ� ����� ������ �־���Ѵ�.

	// ��ǻ�ʹ� IP�ּҶ�� ������ �̿��Ͽ� �ش� ��ǻ���� �ּ������� ������.
	// IP �ּҴ� ũ�� 2������ ������. IPV4 IPV6
	// IPV4 Ÿ���� 32bit �� 4byte�� Ȱ���Ѵ�. �Ϲ������� ����ϴ� IP�ּ��̴�.
	// IPV4�� ǥ�� �Ѱ�� ���� IPV6 Ÿ�� 16byte �ּ� ü�踦 ����� �Ǿ��´�.

	SOCKET ServerSocket;

	// PF_INET�� IPV4 Ÿ���� ������̰�, SOCK_STREAM�� ���븦 ����� ���� ������ ������ ����ڴٴ� �ǹ��̴�.
	// ������ ���ڴ� protocol �� ��� �Ծ��� ����. TCP�� ��������� IPPROTOCOL_TCP�� ����Ѵٰ� �����Ѵ�.
	ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << " fail create Socket : " << GetLastError() << endl; // ������ ���� ���� Ȯ��
		exit(-1);
	}


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
	ServerSockAddr.sin_port = htons(4000);

	// ���ε� �Լ��� ���Ͽ� �ּ� ������ �����Ѵ�.
	// ���� ������ ������ ���ӽ��θ��� ���ش�.
	// ù ���ڷδ� ������ ������ 2��° ���ڴ� �ּ������� ����° ���ڴ� �ι�° ���ڷ� ���� ����ü�� ũ�Ⱑ ����.
	int Result = bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));

	if (Result == SOCKET_ERROR)
	{
		cout << " fail bind : " << GetLastError() << endl; // ������ ���� ���� Ȯ��
		exit(-1);
	}

	// listen �Լ��� ������ �����ϴ� ���·� ������ ���¸� �������ش�.
	// ���� ������ ��ٸ��� ���°� �Ǵ� ���̴�.
	// 2��° ���ڴ� �Ѳ����� ��û ������ �ִ� ���� ���� ���� ���Ѵ�.
	Result = listen(ServerSocket, SOMAXCONN);

	if (Result == SOCKET_ERROR)
	{
		cout << " fail listen : " << GetLastError() << endl; // ������ ���� ���� Ȯ��
		exit(-1);
	}

	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(SOCKADDR_IN));
	int ClientSockAddrLength = sizeof(ClientSockAddr);

	// accept �Լ��� �̿��Ͽ� ���� ��û�� �����Ѵ�. �� �Լ��� ����ȭ�� ������� �����Ѵ�.
	// ����ȭ�� ����̶� ��û�� �������ϱ� �������� ��� ��� ���¿� ���̴� ���� ���Ѵ�.
	// �� ��û�� ������������ �� �Լ��� �Ⱥ������´�.
	// ���� ��û�� �����ϸ� ����� ������ ��������� ���ϵȴ�.
	// ù ���ڷδ� ���� �ι�° ���ڷδ� ���ε� ������ �ּ� ����°�� ����ü�� ũ�Ⱑ ����.

	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);
	
	if (ClientSocket == SOCKET_ERROR)
	{
		cout << " fail accept : " << GetLastError() << endl; // ������ ���� ���� Ȯ��
		exit(-1);
	}

	// Ŭ���̾�Ʈ�� ������ �����ϱ� ���� ������ �����ص� ��Ŷ ũ�⸸ŭ ���۸� �����Ѵ�.
	// recv(����, ���� ������ ���� �迭 �ּ�, �迭�� ũ��, flag)
	// recv �Լ��� ��� �������κ��� ������ ������ �޾��ִ� ������ �Ѵ�.
	// ������ �����Ͱ� ���ٸ� ���⼭ ���� ������ ��� �����·� �ִ´�.
	// flag �����δ� Ȱ������ �������� 0�� �Ѵ�.

	while (true)
	{
		char	Buffer[1024] = { 0, };
		int RecvBytes = recv(ClientSocket, Buffer, 1024, 0);

		cout << "Recive Message : " << Buffer << endl;

		if (RecvBytes <= 0)
		{
			cout << " fail send : " << GetLastError() << endl; // ������ ���� ���� Ȯ��
			exit(-1);
		}

		// ������ Ŭ���̾�Ʈ�� �޽����� ������.
		char	Buffer2[] = "Key,3,Name,gg";
		int SendBytes = send(ClientSocket, Buffer2, sizeof(Buffer2), 0);

		if (SendBytes <= 0)
		{
			cout << " fail recv : " << GetLastError() << endl; // ������ ���� ���� Ȯ��
			exit(-1);
		}
	}

	// ������ �ݾ��ش�.
	closesocket(ClientSocket);
	closesocket(ServerSocket);
	
	// ������ Ȱ���ϴ� ���� WSAStartup �Լ��� WSACleanup ���̿� �ۼ��ؾ��Ѵ�.
	// ���� �����ϸ� �����ڿ� �Ҹ��� ���� �ݴ� ���̴�.
	WSACleanup();
	return 0;

}