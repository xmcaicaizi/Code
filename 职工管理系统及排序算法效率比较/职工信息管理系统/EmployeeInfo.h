#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>

// Ա���ṹ�嶨�� 
typedef struct EmployeeInfo
{
	int no;//���
	char* name;//����
	int depno;//���ű��
	double salary;//����
	char* intro;//���
	EmployeeInfo* next;//��һ��ָ��
}EmployeeInfo;



