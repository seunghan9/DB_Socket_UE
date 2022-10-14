#include "MySQL.h"
#pragma comment (lib, "libmysql.lib")
#include <iostream>
#include <mysql.h>

using namespace std;

MySQL::MySQL()
{
	
	mysql_init(&conn);				// MySQL ���� �ʱ�ȭ
}

MySQL::~MySQL()
{
	
	mysql_close(ConnPtr);			// MySQL ���� ����
}

bool MySQL::ConncetMySQL()
{	// ������ ���̽��� ����
	ConnPtr = mysql_real_connect(&conn, "localhost", "root", "Mytmdgh0910!", "seung0910", 3306, NULL, 0);

	// ���� ��� Ȯ�� Null�� ��� ����
	if (ConnPtr == NULL)
	{
		std::cout << stderr << "Mysql Connection Error : " << mysql_error(&conn);
		return false;
	}

	return true;
}

bool MySQL::RecQueryResult()
{
	// ���� ��û (���̺� �˻�)
	const char* Query = "SELECT * FROM seunghan9";
	Stat = mysql_query(ConnPtr, Query);
	if (Stat != 0)
	{
		std::cout << stderr << "Mysql Connection Error : " << mysql_error(&conn);
		return false;
	}

	// ��û ��� ����
	mysqlResult = mysql_store_result(ConnPtr);

	return true;
}

void MySQL::OutResult()
{
	// ��û ��� ���
	while ((Row = mysql_fetch_row(mysqlResult)) != NULL)
	{
		for (int i = 0; i < mysql_num_fields(mysqlResult); ++i)
		{
			cout << Row[i] << "  ";
		}
		cout << endl;
	}
}
