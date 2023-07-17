#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>

// 员工结构体定义 
typedef struct EmployeeInfo
{
	int no;//编号
	char* name;//名字
	int depno;//部门编号
	double salary;//工资
	char* intro;//简介
	EmployeeInfo* next;//下一个指针
}EmployeeInfo;



