#pragma once
#include "EmployeeInfo.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_LINE 256

//员工信息管理系统结构体
typedef struct ManagementSystem {
	EmployeeInfo* head;  //头指针
	int num;//链表节点数
	EmployeeInfo* lastest;//最后一个链表的指针
} ManagementSystem;

// 将新的员工信息按部门号插入链表
void add_employee_info(ManagementSystem* system, EmployeeInfo* info) {
	// 如果链表为空，直接将新节点作为头节点
	if (system->head == NULL) {
		system->head = info;
		system->lastest = info;
		info->next = NULL;
	}
	else {
		// 如果新节点的工号比头节点小，将新节点作为新的头节点
		if (info->no < system->head->no) {
			info->next = system->head;
			system->head = info;
		}
		else {
			EmployeeInfo* current = system->head;
			EmployeeInfo* previous = NULL;

			// 在链表中找到位置
			while (current != NULL && info->no > current->no) {
				previous = current;
				current = current->next;
				if (current->no == info->no)
				{
					printf("员工工号重复！\n");
					return;
				}
			}

			// 将新节点插入到链表中
			info->next = current;
			previous->next = info;
		}
	}

	system->num++; // 更新节点数
}


// 创建并初始化ManagementSystem
ManagementSystem MakeManagementSystem()
{
	ManagementSystem system = {};
	system.num = 0;
	system.head = NULL;
	system.lastest = NULL;
	return system;
}

// 在infos数组中查找具有给定员工号的员工信息，然后用新的信息替换旧的信息
void modify_employee_info(ManagementSystem* system, int no, char* name)
{
	EmployeeInfo* current = system->head;

	while (current != NULL)
	{
		if (current->no == no && strcmp(current->name, name) == 0)
		{
			printf(" 口-------------------------------------------------------------------口\n");
			printf(" || 工号 | 姓名                 | 部门编号|   工资  |  简介           ||\n");
			printf(" || %-4d | %-20s | %-7d | %.2lf | %-15s ||\n", current->no, current->name, current->depno, current->salary, current->intro);
			printf(" 口-------------------------------------------------------------------口\n");
			printf(" 请输入需要修改的信息:\n");
			printf(" 1.工号\n");
			printf(" 2.姓名\n");
			printf(" 3.部门编号\n");
			printf(" 4.工资\n");
			printf(" 5.简介\n");
			printf(" 6.全部信息\n");
			printf(" 0.返回上级\n");
			printf(" 请输入需要修改的选项: ");
			int m = 0;
			scanf("%d", &m);

			switch (m)
			{
			case 1:
				printf(" 请输入修改后的工号: ");
				scanf("%d", &(current->no));
				break;
			case 2:
				printf(" 请输入修改后的姓名: ");
				scanf("%s", current->name);
				break;
			case 3:
				printf(" 请输入修改后的部门编号: ");
				scanf("%d", &(current->depno));
				break;
			case 4:
				printf(" 请输入修改后的工资: ");
				scanf("%lf", &(current->salary));
				break;
			case 5:
				printf(" 请输入修改后的简介: ");
				scanf("%s", current->intro);
				break;
			case 6:
				printf(" 请输入修改后的工号 姓名 部门编号 工资 简介: ");
				scanf("%d %s %d %lf %s", &(current->no), current->name, &(current->depno), &(current->salary), current->intro);
				break;
			case 0:
				return;
				break;
			default:
				printf(" 无效选项!\n");
				break;
			}

			printf(" 修改后的信息：\n");
			printf(" 口-------------------------------------------------------------------口\n");
			printf(" || 工号 | 姓名                 | 部门编号|   工资  |  简介           ||\n");
			printf(" || %-4d | %-20s | %-7d | %.2lf | %-15s ||\n", current->no, current->name, current->depno, current->salary, current->intro);
			printf(" 口-------------------------------------------------------------------口\n");
			return;
		}
		current = current->next;
	}

	printf(" 未找到工号为 %d 姓名为 %s 的员工.\n", no, name);
}




// 在链表中查找具有给定员工号的员工信息，然后从链表中删除该信息
void delete_employee_info(ManagementSystem* system, int no, char* name)
{
	EmployeeInfo* current = system->head;
	EmployeeInfo* previous = NULL;

	while (current != NULL) {
		if (current->no == no && strcmp(current->name, name) == 0) {
			if (previous == NULL) {
				// 如果要删除的节点是头节点
				system->head = current->next;
			}
			else {
				// 如果要删除的节点是其他节点
				previous->next = current->next;
				// 如果删除的是最后一个节点，更新lastest
				if (current == system->lastest) {
					system->lastest = previous;
				}
			}
			// 释放节点内存
			free(current->name);
			free(current->intro);
			free(current);
			system->num--;
			printf("已经删除!\n");
			return;
		}
		previous = current;
		current = current->next;
	}

	printf(" 未找到工号为 %d 姓名为 %s 的员工.\n", no, name);
}


// 进行选择排序(升序)
void sort_employee(ManagementSystem* system, int choice) {
	EmployeeInfo* sorted = NULL;  // 新的排序链表头
	EmployeeInfo* last = NULL;    // 新的排序链表尾部

	switch (choice) {
	case 1: // 按工号排序
		while (system->head != NULL) {
			// 寻找最小的节点
			EmployeeInfo* min = system->head;
			EmployeeInfo** pointer = &(system->head);

			for (EmployeeInfo** p = &(system->head->next); *p != NULL; p = &((*p)->next)) {
				if ((*p)->no < min->no) {
					min = *p;
					pointer = p;  // 保存最小节点的前一个节点的指针
				}
			}

			// 从原链表中移除最小节点
			*pointer = min->next;

			// 将最小节点添加到新链表的末尾
			min->next = NULL;
			if (sorted == NULL) {
				// 如果新链表为空，设置头和尾为最小节点
				sorted = last = min;
			}
			else {
				// 如果新链表不为空，添加到尾部并更新尾部节点
				last->next = min;
				last = min;
			}
		}
		break;
	case 2: // 按部门排序
		while (system->head != NULL) {
			// 寻找最小的节点
			EmployeeInfo* min = system->head;
			EmployeeInfo** pointer = &(system->head);

			for (EmployeeInfo** p = &(system->head->next); *p != NULL; p = &((*p)->next)) {
				// 按部门号排序
				if ((*p)->depno < min->depno) {
					min = *p;
					pointer = p;  // 保存最小节点的前一个节点的指针
				}
				// 部门号相等时，比较名字长度
				else if ((*p)->depno == min->depno) {
					if (strlen((*p)->name) < strlen(min->name)) {
						min = *p;
						pointer = p;  // 保存最小节点的前一个节点的指针
					}
				}
			}

			// 从原链表中移除最小节点
			*pointer = min->next;

			// 将最小节点添加到新链表的末尾
			min->next = NULL;
			if (sorted == NULL) {
				// 如果新链表为空，设置头和尾为最小节点
				sorted = last = min;
			}
			else {
				// 如果新链表不为空，添加到尾部并更新尾部节点
				last->next = min;
				last = min;
			}
		}
		break;
	case 3: // 按工资排序
		while (system->head != NULL) {
			// 寻找最小的节点
			EmployeeInfo* min = system->head;
			EmployeeInfo** pointer = &(system->head);

			for (EmployeeInfo** p = &(system->head->next); *p != NULL; p = &((*p)->next)) {
				if ((*p)->salary < min->salary) {
					min = *p;
					pointer = p;  // 保存最小节点的前一个节点的指针
				}
			}

			// 从原链表中移除最小节点
			*pointer = min->next;

			// 将最小节点添加到新链表的末尾
			min->next = NULL;
			if (sorted == NULL) {
				// 如果新链表为空，设置头和尾为最小节点
				sorted = last = min;
			}
			else {
				// 如果新链表不为空，添加到尾部并更新尾部节点
				last->next = min;
				last = min;
			}
		}
		break;
	default:
		printf("无效选项!\n");
		return;
	}

	// 更新头节点
	system->head = sorted;
}


// 在链表中查找具有给定员工号的员工信息，并返回找到的信息
EmployeeInfo* find_employee_info_by_no(ManagementSystem* system, int no, const char* name)
{
	EmployeeInfo* current = system->head;
	while (current != NULL) {
		if (current->no == no && strcmp(current->name, name) == 0) {
			return current;
		}
		current = current->next;
	}
	// 如果没有找到，则返回NULL
	return NULL;
}


//从文件读取
void load_employee_info_from_file(ManagementSystem* system, FILE* fp) {
	if (fp == NULL) {
		printf("Error: Cannot open file 员工信息\n");
		return;
	}

	char line[MAX_LINE];
	while (fgets(line, sizeof(line), fp)) {
		EmployeeInfo* info = (EmployeeInfo*)malloc(sizeof(EmployeeInfo)); //动态分配内存
		char name[MAX_LINE] = {};
		char intro[MAX_LINE];
		if (sscanf(line, "%d %s %d %lf %s", &(info->no), name, &(info->depno), &(info->salary), intro) == 5) {
			info->name = _strdup(name);  //拷贝字符串
			info->intro = _strdup(intro);
			add_employee_info(system, info);
		}
		else {
			printf("Error: 文件格式错误\n");
			break;
		}
	}

	fclose(fp);
}

//保存回文件
void save_employee_info_to_file(ManagementSystem* system, FILE* fp)
{
	if (fp == NULL)
	{
		printf("Error: Cannot open file 员工信息");
		return;
	}

	EmployeeInfo* current = system->head;
	while (current != NULL)
	{
		fprintf(fp, "%d %s %d %.2lf %s\n", current->no, current->name, current->depno, current->salary, current->intro);
		current = current->next;
	}

	fclose(fp);
}


// 打印所有员工
void print_all_employee_info(ManagementSystem* system) {
	printf(" 打印所有员工信息\n");
	printf(" 口-------------------------------------------------------------------口\n");
	printf(" || 工号 | 姓名                 | 部门编号|   工资  |  简介           ||\n");
	printf(" 口-------------------------------------------------------------------口\n");
	EmployeeInfo* current_node = system->head;
	while (current_node != NULL) {
		printf(" || %-4d | %-20s | %-7d | %.2lf | %-15s ||\n", current_node->no, current_node->name, current_node->depno, current_node->salary, current_node->intro);
		current_node = current_node->next;
	}
	printf(" 口-------------------------------------------------------------------口\n");
}

//统计各部门员工数
void count_department_employee(ManagementSystem* system) {
	int department_counts[5] = { 0 };

	EmployeeInfo* current_node = system->head;
	while (current_node != NULL) {
		int dep_index = (current_node->depno % 1000) - 1;
		if (dep_index >= 0 && dep_index < 5) {
			department_counts[dep_index]++;
		}
		current_node = current_node->next;
	}

	for (int i = 0; i < 5; i++) {
		printf("部门 %d 有 %d 个员工\n", i + 1001, department_counts[i]);
	}
}


//释放ManagementSystem的内存
void FreeManagementSystem(ManagementSystem* system)
{
	if (system == NULL) {
		return;
	}

	// 先释放 EmployeeInfo 链表的内存
	EmployeeInfo* current = system->head;
	while (current != NULL) {
		EmployeeInfo* next = current->next;
		free(current->name); // 释放name字符串的内存
		free(current->intro); // 释放intro字符串的内存
		free(current); // 释放当前节点的内存
		current = next;
	}

	// 将头指针设为 NULL 和 num 设为 0
	system->head = NULL;
	system->num = 0;
	system->lastest = NULL;
}

//职工管理系统菜单
void systemmenu() {
	ManagementSystem System = MakeManagementSystem();

	while (1)
	{
		system("cls");

		printf(" 欢迎使用员工信息管理系统!\n");
		printf(" 口---------------------口\n");
		printf(" ||1.  从文件读取\t||\n");
		printf(" ||2.  保存\t\t||\n");
		printf(" ||3.  添加新员工信息\t||\n");
		printf(" ||4.  修改员工信息\t||\n");
		printf(" ||5.  删除员工信息\t||\n");
		printf(" ||6.  员工信息排序\t||\n");
		printf(" ||7.  查找员工信息\t||\n");
		printf(" ||8.  打印所有员工信息\t||\n");
		printf(" ||9.  统计部门员工数\t||\n");
		printf(" ||0.  退出\t\t||\n");
		printf(" 口---------------------口\n");
		printf("输入按键使用功能:");
		int choice;
		FILE* fp;
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
		{
			fp = fopen("员工信息.txt", "r");
			printf("正在导入。。。\n");
			load_employee_info_from_file(&System, fp);
			printf("导入成功");
			system("pause");
			break;
		}
		case 2:
		{
			fp = fopen("员工信息.txt", "w");
			save_employee_info_to_file(&System, fp);
			break;
		}
		case 3:
		{
			EmployeeInfo* info = (EmployeeInfo*)malloc(sizeof(EmployeeInfo));
			char name[MAX_LINE];
			char intro[MAX_LINE];
			printf("输入员工编号 姓名 部门编号 工资 简介(每项用空格隔开):");
			scanf("%d %s %d %lf %s", &(info->no), name, &(info->depno), &(info->salary), intro);
			info->name = _strdup(name);
			info->intro = _strdup(intro);
			add_employee_info(&System, info);
			system("pause");
			break;
		}
		case 4:
		{
			printf("请输入需要修改信息的员工工号 和 姓名(用空格隔开)：");
			int no;
			char name[MAX_LINE];
			scanf("%d %s", &no, name);
			modify_employee_info(&System, no, name);
			system("pause");
			break;
		}
		case 5:
		{
			printf("请输入需要删除信息的员工工号 和 姓名(用空格隔开)：");
			int no;
			char name[MAX_LINE];
			scanf("%d %s", &no, name);
			delete_employee_info(&System, no, name);
			system("pause");
			break;
		}
		case 6:
		{
			printf("请选择排序方式:\n");
			printf("1. 按工号排序\n");
			printf("2. 按部门排序\n");
			printf("3. 按工资排序\n");
			printf("0. 返回上级\n");
			int sortChoice;
			printf("请输入选项:");
			scanf("%d", &sortChoice);
			if (sortChoice == 0) break;
			sort_employee(&System, sortChoice);
			printf("排序完毕!\n");
			system("pause");
			break;
		}
		case 7:
		{
			int no;
			printf("请输入需要查找信息的员工工号 和 姓名(用空格隔开)：");
			char name[MAX_LINE];
			scanf("%d %s", &no, name);
			EmployeeInfo* info = find_employee_info_by_no(&System, no, name);
			if (info != NULL)
			{
				printf(" 口-------------------------------------------------------------------口\n");
				printf(" || 工号 | 姓名                 | 部门编号|   工资  |  简介           ||\n");
				printf(" || %-4d | %-20s | %-7d | %.2lf | %-15s ||\n", info->no, info->name, info->depno, info->salary, info->intro);
				printf(" 口-------------------------------------------------------------------口\n");
			}
			else
			{
				printf("未找到该员工\n");
			}
			system("pause");
			break;
		}
		case 8:
		{
			print_all_employee_info(&System);
			system("pause");  // 暂停等待用户按键继续
			break;
		}
		case 9:
		{
			count_department_employee(&System);
			system("pause");  // 暂停等待用户按键继续
			break;
		}
		case 0:
		{
			FreeManagementSystem(&System);
			return;
		}
		default:
		{
			printf("无效选项\n");
		}
		}
	}

	return;
}