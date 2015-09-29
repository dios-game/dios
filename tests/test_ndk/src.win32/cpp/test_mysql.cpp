#include "precompiled.h"
#include "mysql.h"    

int TestMysql()
{
	int res, j;
	MYSQL mysql;
	MYSQL_RES *resultset;
	MYSQL_ROW row;
	mysql_init(&mysql);// 初始化mysql结构    
	//连接本机，用户名是root,密码是hope,数据库是hope,端口是3306  
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "123456", "test", 3306, NULL, 0))
	{
		printf("\n数据库连接发生错误 %d!", mysql_errno(&mysql));
	}
	else
	{
		printf("\n数据库连接成功!\n");  //插入一条数据到数据库  
		res = mysql_query(&mysql, "insert into student(name,age,rollno) values('elisa',33,'3')");
		if (!res)
		{
			printf("插入%lu行数据成功!\n", (unsigned long)mysql_affected_rows(&mysql));
		}
		else printf("插入数据失败!\n");

		if (mysql_query(&mysql, "select * from student"))
		{
			printf("数据库查询发生错误");
		}
		else
		{
			//检索数据   
			printf("\n查询数据为:\n");
			resultset = mysql_store_result(&mysql);// 获得结果集           
			if (mysql_num_rows(resultset) != NULL)
			{
				int numRows = mysql_num_rows(resultset); // 获得结果集中的记录数  
				int numFields = mysql_num_fields(resultset);// 获得表中字段数  
				printf("共 %d 行记录，每行 %d 个字段。", numRows, numFields);
				j = 1;
				while (row = mysql_fetch_row(resultset))
				{
					int i = 0;
					printf("\n 第 %d 行：", j);
					for (i = 0; i < numFields; i++)
					{
						fprintf(stdout, " %s", row[i]); // 打印字段值  
					}
					j++;
				}
			}
			else
			{
				printf("\n无查询结果!");
			}
			mysql_free_result(resultset);  // 释放结果集  
		}
	}
	mysql_close(&mysql); // 释放数据库连接   
	fgetchar();
	return 0;
}