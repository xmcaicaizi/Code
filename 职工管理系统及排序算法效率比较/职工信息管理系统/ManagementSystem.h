#pragma once
#include "EmployeeInfo.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_LINE 256

//Ա����Ϣ����ϵͳ�ṹ��
typedef struct ManagementSystem {
	EmployeeInfo* head;  //ͷָ��
	int num;//����ڵ���
	EmployeeInfo* lastest;//���һ�������ָ��
} ManagementSystem;

// ���µ�Ա����Ϣ�����źŲ�������
void add_employee_info(ManagementSystem* system, EmployeeInfo* info) {
	// �������Ϊ�գ�ֱ�ӽ��½ڵ���Ϊͷ�ڵ�
	if (system->head == NULL) {
		system->head = info;
		system->lastest = info;
		info->next = NULL;
	}
	else {
		// ����½ڵ�Ĺ��ű�ͷ�ڵ�С�����½ڵ���Ϊ�µ�ͷ�ڵ�
		if (info->no < system->head->no) {
			info->next = system->head;
			system->head = info;
		}
		else {
			EmployeeInfo* current = system->head;
			EmployeeInfo* previous = NULL;

			// ���������ҵ�λ��
			while (current != NULL && info->no > current->no) {
				previous = current;
				current = current->next;
				if (current->no == info->no)
				{
					printf("Ա�������ظ���\n");
					return;
				}
			}

			// ���½ڵ���뵽������
			info->next = current;
			previous->next = info;
		}
	}

	system->num++; // ���½ڵ���
}


// ��������ʼ��ManagementSystem
ManagementSystem MakeManagementSystem()
{
	ManagementSystem system = {};
	system.num = 0;
	system.head = NULL;
	system.lastest = NULL;
	return system;
}

// ��infos�����в��Ҿ��и���Ա���ŵ�Ա����Ϣ��Ȼ�����µ���Ϣ�滻�ɵ���Ϣ
void modify_employee_info(ManagementSystem* system, int no, char* name)
{
	EmployeeInfo* current = system->head;

	while (current != NULL)
	{
		if (current->no == no && strcmp(current->name, name) == 0)
		{
			printf(" ��-------------------------------------------------------------------��\n");
			printf(" || ���� | ����                 | ���ű��|   ����  |  ���           ||\n");
			printf(" || %-4d | %-20s | %-7d | %.2lf | %-15s ||\n", current->no, current->name, current->depno, current->salary, current->intro);
			printf(" ��-------------------------------------------------------------------��\n");
			printf(" ��������Ҫ�޸ĵ���Ϣ:\n");
			printf(" 1.����\n");
			printf(" 2.����\n");
			printf(" 3.���ű��\n");
			printf(" 4.����\n");
			printf(" 5.���\n");
			printf(" 6.ȫ����Ϣ\n");
			printf(" 0.�����ϼ�\n");
			printf(" ��������Ҫ�޸ĵ�ѡ��: ");
			int m = 0;
			scanf("%d", &m);

			switch (m)
			{
			case 1:
				printf(" �������޸ĺ�Ĺ���: ");
				scanf("%d", &(current->no));
				break;
			case 2:
				printf(" �������޸ĺ������: ");
				scanf("%s", current->name);
				break;
			case 3:
				printf(" �������޸ĺ�Ĳ��ű��: ");
				scanf("%d", &(current->depno));
				break;
			case 4:
				printf(" �������޸ĺ�Ĺ���: ");
				scanf("%lf", &(current->salary));
				break;
			case 5:
				printf(" �������޸ĺ�ļ��: ");
				scanf("%s", current->intro);
				break;
			case 6:
				printf(" �������޸ĺ�Ĺ��� ���� ���ű�� ���� ���: ");
				scanf("%d %s %d %lf %s", &(current->no), current->name, &(current->depno), &(current->salary), current->intro);
				break;
			case 0:
				return;
				break;
			default:
				printf(" ��Чѡ��!\n");
				break;
			}

			printf(" �޸ĺ����Ϣ��\n");
			printf(" ��-------------------------------------------------------------------��\n");
			printf(" || ���� | ����                 | ���ű��|   ����  |  ���           ||\n");
			printf(" || %-4d | %-20s | %-7d | %.2lf | %-15s ||\n", current->no, current->name, current->depno, current->salary, current->intro);
			printf(" ��-------------------------------------------------------------------��\n");
			return;
		}
		current = current->next;
	}

	printf(" δ�ҵ�����Ϊ %d ����Ϊ %s ��Ա��.\n", no, name);
}




// �������в��Ҿ��и���Ա���ŵ�Ա����Ϣ��Ȼ���������ɾ������Ϣ
void delete_employee_info(ManagementSystem* system, int no, char* name)
{
	EmployeeInfo* current = system->head;
	EmployeeInfo* previous = NULL;

	while (current != NULL) {
		if (current->no == no && strcmp(current->name, name) == 0) {
			if (previous == NULL) {
				// ���Ҫɾ���Ľڵ���ͷ�ڵ�
				system->head = current->next;
			}
			else {
				// ���Ҫɾ���Ľڵ��������ڵ�
				previous->next = current->next;
				// ���ɾ���������һ���ڵ㣬����lastest
				if (current == system->lastest) {
					system->lastest = previous;
				}
			}
			// �ͷŽڵ��ڴ�
			free(current->name);
			free(current->intro);
			free(current);
			system->num--;
			printf("�Ѿ�ɾ��!\n");
			return;
		}
		previous = current;
		current = current->next;
	}

	printf(" δ�ҵ�����Ϊ %d ����Ϊ %s ��Ա��.\n", no, name);
}


// ����ѡ������(����)
void sort_employee(ManagementSystem* system, int choice) {
	EmployeeInfo* sorted = NULL;  // �µ���������ͷ
	EmployeeInfo* last = NULL;    // �µ���������β��

	switch (choice) {
	case 1: // ����������
		while (system->head != NULL) {
			// Ѱ����С�Ľڵ�
			EmployeeInfo* min = system->head;
			EmployeeInfo** pointer = &(system->head);

			for (EmployeeInfo** p = &(system->head->next); *p != NULL; p = &((*p)->next)) {
				if ((*p)->no < min->no) {
					min = *p;
					pointer = p;  // ������С�ڵ��ǰһ���ڵ��ָ��
				}
			}

			// ��ԭ�������Ƴ���С�ڵ�
			*pointer = min->next;

			// ����С�ڵ���ӵ��������ĩβ
			min->next = NULL;
			if (sorted == NULL) {
				// ���������Ϊ�գ�����ͷ��βΪ��С�ڵ�
				sorted = last = min;
			}
			else {
				// ���������Ϊ�գ���ӵ�β��������β���ڵ�
				last->next = min;
				last = min;
			}
		}
		break;
	case 2: // ����������
		while (system->head != NULL) {
			// Ѱ����С�Ľڵ�
			EmployeeInfo* min = system->head;
			EmployeeInfo** pointer = &(system->head);

			for (EmployeeInfo** p = &(system->head->next); *p != NULL; p = &((*p)->next)) {
				// �����ź�����
				if ((*p)->depno < min->depno) {
					min = *p;
					pointer = p;  // ������С�ڵ��ǰһ���ڵ��ָ��
				}
				// ���ź����ʱ���Ƚ����ֳ���
				else if ((*p)->depno == min->depno) {
					if (strlen((*p)->name) < strlen(min->name)) {
						min = *p;
						pointer = p;  // ������С�ڵ��ǰһ���ڵ��ָ��
					}
				}
			}

			// ��ԭ�������Ƴ���С�ڵ�
			*pointer = min->next;

			// ����С�ڵ���ӵ��������ĩβ
			min->next = NULL;
			if (sorted == NULL) {
				// ���������Ϊ�գ�����ͷ��βΪ��С�ڵ�
				sorted = last = min;
			}
			else {
				// ���������Ϊ�գ���ӵ�β��������β���ڵ�
				last->next = min;
				last = min;
			}
		}
		break;
	case 3: // ����������
		while (system->head != NULL) {
			// Ѱ����С�Ľڵ�
			EmployeeInfo* min = system->head;
			EmployeeInfo** pointer = &(system->head);

			for (EmployeeInfo** p = &(system->head->next); *p != NULL; p = &((*p)->next)) {
				if ((*p)->salary < min->salary) {
					min = *p;
					pointer = p;  // ������С�ڵ��ǰһ���ڵ��ָ��
				}
			}

			// ��ԭ�������Ƴ���С�ڵ�
			*pointer = min->next;

			// ����С�ڵ���ӵ��������ĩβ
			min->next = NULL;
			if (sorted == NULL) {
				// ���������Ϊ�գ�����ͷ��βΪ��С�ڵ�
				sorted = last = min;
			}
			else {
				// ���������Ϊ�գ���ӵ�β��������β���ڵ�
				last->next = min;
				last = min;
			}
		}
		break;
	default:
		printf("��Чѡ��!\n");
		return;
	}

	// ����ͷ�ڵ�
	system->head = sorted;
}


// �������в��Ҿ��и���Ա���ŵ�Ա����Ϣ���������ҵ�����Ϣ
EmployeeInfo* find_employee_info_by_no(ManagementSystem* system, int no, const char* name)
{
	EmployeeInfo* current = system->head;
	while (current != NULL) {
		if (current->no == no && strcmp(current->name, name) == 0) {
			return current;
		}
		current = current->next;
	}
	// ���û���ҵ����򷵻�NULL
	return NULL;
}


//���ļ���ȡ
void load_employee_info_from_file(ManagementSystem* system, FILE* fp) {
	if (fp == NULL) {
		printf("Error: Cannot open file Ա����Ϣ\n");
		return;
	}

	char line[MAX_LINE];
	while (fgets(line, sizeof(line), fp)) {
		EmployeeInfo* info = (EmployeeInfo*)malloc(sizeof(EmployeeInfo)); //��̬�����ڴ�
		char name[MAX_LINE] = {};
		char intro[MAX_LINE];
		if (sscanf(line, "%d %s %d %lf %s", &(info->no), name, &(info->depno), &(info->salary), intro) == 5) {
			info->name = _strdup(name);  //�����ַ���
			info->intro = _strdup(intro);
			add_employee_info(system, info);
		}
		else {
			printf("Error: �ļ���ʽ����\n");
			break;
		}
	}

	fclose(fp);
}

//������ļ�
void save_employee_info_to_file(ManagementSystem* system, FILE* fp)
{
	if (fp == NULL)
	{
		printf("Error: Cannot open file Ա����Ϣ");
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


// ��ӡ����Ա��
void print_all_employee_info(ManagementSystem* system) {
	printf(" ��ӡ����Ա����Ϣ\n");
	printf(" ��-------------------------------------------------------------------��\n");
	printf(" || ���� | ����                 | ���ű��|   ����  |  ���           ||\n");
	printf(" ��-------------------------------------------------------------------��\n");
	EmployeeInfo* current_node = system->head;
	while (current_node != NULL) {
		printf(" || %-4d | %-20s | %-7d | %.2lf | %-15s ||\n", current_node->no, current_node->name, current_node->depno, current_node->salary, current_node->intro);
		current_node = current_node->next;
	}
	printf(" ��-------------------------------------------------------------------��\n");
}

//ͳ�Ƹ�����Ա����
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
		printf("���� %d �� %d ��Ա��\n", i + 1001, department_counts[i]);
	}
}


//�ͷ�ManagementSystem���ڴ�
void FreeManagementSystem(ManagementSystem* system)
{
	if (system == NULL) {
		return;
	}

	// ���ͷ� EmployeeInfo ������ڴ�
	EmployeeInfo* current = system->head;
	while (current != NULL) {
		EmployeeInfo* next = current->next;
		free(current->name); // �ͷ�name�ַ������ڴ�
		free(current->intro); // �ͷ�intro�ַ������ڴ�
		free(current); // �ͷŵ�ǰ�ڵ���ڴ�
		current = next;
	}

	// ��ͷָ����Ϊ NULL �� num ��Ϊ 0
	system->head = NULL;
	system->num = 0;
	system->lastest = NULL;
}

//ְ������ϵͳ�˵�
void systemmenu() {
	ManagementSystem System = MakeManagementSystem();

	while (1)
	{
		system("cls");

		printf(" ��ӭʹ��Ա����Ϣ����ϵͳ!\n");
		printf(" ��---------------------��\n");
		printf(" ||1.  ���ļ���ȡ\t||\n");
		printf(" ||2.  ����\t\t||\n");
		printf(" ||3.  �����Ա����Ϣ\t||\n");
		printf(" ||4.  �޸�Ա����Ϣ\t||\n");
		printf(" ||5.  ɾ��Ա����Ϣ\t||\n");
		printf(" ||6.  Ա����Ϣ����\t||\n");
		printf(" ||7.  ����Ա����Ϣ\t||\n");
		printf(" ||8.  ��ӡ����Ա����Ϣ\t||\n");
		printf(" ||9.  ͳ�Ʋ���Ա����\t||\n");
		printf(" ||0.  �˳�\t\t||\n");
		printf(" ��---------------------��\n");
		printf("���밴��ʹ�ù���:");
		int choice;
		FILE* fp;
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
		{
			fp = fopen("Ա����Ϣ.txt", "r");
			printf("���ڵ��롣����\n");
			load_employee_info_from_file(&System, fp);
			printf("����ɹ�");
			system("pause");
			break;
		}
		case 2:
		{
			fp = fopen("Ա����Ϣ.txt", "w");
			save_employee_info_to_file(&System, fp);
			break;
		}
		case 3:
		{
			EmployeeInfo* info = (EmployeeInfo*)malloc(sizeof(EmployeeInfo));
			char name[MAX_LINE];
			char intro[MAX_LINE];
			printf("����Ա����� ���� ���ű�� ���� ���(ÿ���ÿո����):");
			scanf("%d %s %d %lf %s", &(info->no), name, &(info->depno), &(info->salary), intro);
			info->name = _strdup(name);
			info->intro = _strdup(intro);
			add_employee_info(&System, info);
			system("pause");
			break;
		}
		case 4:
		{
			printf("��������Ҫ�޸���Ϣ��Ա������ �� ����(�ÿո����)��");
			int no;
			char name[MAX_LINE];
			scanf("%d %s", &no, name);
			modify_employee_info(&System, no, name);
			system("pause");
			break;
		}
		case 5:
		{
			printf("��������Ҫɾ����Ϣ��Ա������ �� ����(�ÿո����)��");
			int no;
			char name[MAX_LINE];
			scanf("%d %s", &no, name);
			delete_employee_info(&System, no, name);
			system("pause");
			break;
		}
		case 6:
		{
			printf("��ѡ������ʽ:\n");
			printf("1. ����������\n");
			printf("2. ����������\n");
			printf("3. ����������\n");
			printf("0. �����ϼ�\n");
			int sortChoice;
			printf("������ѡ��:");
			scanf("%d", &sortChoice);
			if (sortChoice == 0) break;
			sort_employee(&System, sortChoice);
			printf("�������!\n");
			system("pause");
			break;
		}
		case 7:
		{
			int no;
			printf("��������Ҫ������Ϣ��Ա������ �� ����(�ÿո����)��");
			char name[MAX_LINE];
			scanf("%d %s", &no, name);
			EmployeeInfo* info = find_employee_info_by_no(&System, no, name);
			if (info != NULL)
			{
				printf(" ��-------------------------------------------------------------------��\n");
				printf(" || ���� | ����                 | ���ű��|   ����  |  ���           ||\n");
				printf(" || %-4d | %-20s | %-7d | %.2lf | %-15s ||\n", info->no, info->name, info->depno, info->salary, info->intro);
				printf(" ��-------------------------------------------------------------------��\n");
			}
			else
			{
				printf("δ�ҵ���Ա��\n");
			}
			system("pause");
			break;
		}
		case 8:
		{
			print_all_employee_info(&System);
			system("pause");  // ��ͣ�ȴ��û���������
			break;
		}
		case 9:
		{
			count_department_employee(&System);
			system("pause");  // ��ͣ�ȴ��û���������
			break;
		}
		case 0:
		{
			FreeManagementSystem(&System);
			return;
		}
		default:
		{
			printf("��Чѡ��\n");
		}
		}
	}

	return;
}