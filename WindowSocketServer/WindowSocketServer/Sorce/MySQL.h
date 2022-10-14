#pragma once

#pragma comment (lib, "libmysql.lib")

#include <mysql.h>

class MySQL
{
public:
	MySQL();
	~MySQL();

public:
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

public:
	// Query ����
	bool ConncetMySQL();
	// Query ��� �ޱ�
	bool RecQueryResult();
	// Query ��� ���
	void OutResult();

};

