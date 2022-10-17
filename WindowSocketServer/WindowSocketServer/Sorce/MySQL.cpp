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
	while ((Row = mysql_fetch_row(mysqlResult)) != NULL)
	{
		for (unsigned int i = 0; i < mysql_num_fields(mysqlResult); ++i)
		{
			std::cout << Row[i] << "  ";
		}
		std::cout << std::endl;
	}
}

void MySQL::Insert(SpawnActorInfo& ActorInfo)
{
	//while ((Row = mysql_fetch_row(mysqlResult)) != NULL)
	//{
	Row = mysql_fetch_row(mysqlResult);

	for (unsigned int i = 0; i < mysql_num_fields(mysqlResult); ++i)
	{
		switch (i)
		{
		case 0:
			ActorInfo.Key = stoi(Row[i]);
			break;
		case 1:
			ActorInfo.Name = Row[i];
			break;
		case 2:
			ActorInfo.VectorInfo.x = stoi(Row[i]);
			break;
		case 3:
			ActorInfo.VectorInfo.y = stoi(Row[i]);
			break;
		case 4:
			ActorInfo.VectorInfo.z = stoi(Row[i]);
			break;

		}


	}
}
