#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "ManagementSystem.h"
#include "paixu.h"
#include <stdio.h>
#include <windows.h>

int main() {
    while (1)
    {
        system("cls");
        printf("欢迎使用系统!\n");
        printf("口---------------------口\n");
        printf("||1.  员工信息管理系统\t||\n");
        printf("||2.  排序算法测试\t||\n");
        printf("||0.  退出\t\t||\n");
        printf("口---------------------口\n");
        printf("输入按键使用功能:");

        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            // 员工信息管理系统
            systemmenu();
            break;
        case 2:
            // 排序算法测试
            SortTest();
            break;
        case 0:
            // 退出程序
            printf("感谢使用，再见！\n");
            return 0;
        default:
            printf("无效选项\n");
        }
        system("pause");  // 暂停等待用户按键继续
    }

    return 0;
}
