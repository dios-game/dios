#include "precompiled.h"
#include "mysql.h"    

int TestMysql()
{
	int res, j;
	MYSQL mysql;
	MYSQL_RES *resultset;
	MYSQL_ROW row;
	mysql_init(&mysql);// ��ʼ��mysql�ṹ    
	//���ӱ������û�����root,������hope,���ݿ���hope,�˿���3306  
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "123456", "test", 3306, NULL, 0))
	{
		printf("\n���ݿ����ӷ������� %d!", mysql_errno(&mysql));
	}
	else
	{
		printf("\n���ݿ����ӳɹ�!\n");  //����һ�����ݵ����ݿ�  
		res = mysql_query(&mysql, "insert into student(name,age,rollno) values('elisa',33,'3')");
		if (!res)
		{
			printf("����%lu�����ݳɹ�!\n", (unsigned long)mysql_affected_rows(&mysql));
		}
		else printf("��������ʧ��!\n");

		if (mysql_query(&mysql, "select * from student"))
		{
			printf("���ݿ��ѯ��������");
		}
		else
		{
			//��������   
			printf("\n��ѯ����Ϊ:\n");
			resultset = mysql_store_result(&mysql);// ��ý����           
			if (mysql_num_rows(resultset) != NULL)
			{
				int numRows = mysql_num_rows(resultset); // ��ý�����еļ�¼��  
				int numFields = mysql_num_fields(resultset);// ��ñ����ֶ���  
				printf("�� %d �м�¼��ÿ�� %d ���ֶΡ�", numRows, numFields);
				j = 1;
				while (row = mysql_fetch_row(resultset))
				{
					int i = 0;
					printf("\n �� %d �У�", j);
					for (i = 0; i < numFields; i++)
					{
						fprintf(stdout, " %s", row[i]); // ��ӡ�ֶ�ֵ  
					}
					j++;
				}
			}
			else
			{
				printf("\n�޲�ѯ���!");
			}
			mysql_free_result(resultset);  // �ͷŽ����  
		}
	}
	mysql_close(&mysql); // �ͷ����ݿ�����   
	fgetchar();
	return 0;
}