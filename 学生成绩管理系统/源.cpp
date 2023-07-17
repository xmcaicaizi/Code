//头文件
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<stdio.h>
#include <iostream>
#include<string.h>
using namespace std;



//结构体数据
typedef struct _Student
{
    char name[20];//学生姓名
    int snum;//学号
    int zuoye[3];//作业完成情况
    double score;//平时分
    int rank;//排名
}Student;


//节点
typedef struct _Node {
    Student stu;//学生
    struct _Node* pnext;//指向下一个节点的指针
}Node;


//头节点
Node* g_phead = NULL;//什么都没有,空


//函数声明
void menu();//开始界面
void cjmenu();//1.0成绩菜单
void sdsr();//1.1手动输入
void wjdr();//1.2文件导入
void cxcj();//2.查询成绩
void tjpjf();//3.统计平时间分
void zytj();//4.作业统计
void sccj();//5.删除成绩
void amzsc(char fname[20]);//5.1按名字删除
void axhsc(int fnum);//5.2按学号删除
void xgcj();//6.修改成绩
void xhcz();//6.1学号查找
void xmcz();//6.2姓名查找
void xg(Node* p);//6.3找到后修改
void zdpm();//7自动排名
void bcbtc();//0.保存并退出





int main()
{
    menu();
}


//开始菜单
void menu()
{
    system("cls");
    cout << "|-----------------------------------------------------|\n";
    cout << "|欢迎使用学生成绩管理系统                             |\n";
    cout << "|-----------------------------------------------------|\n";
    cout << "|\t\t1.输入成绩                            |\n";
    cout << "|\t\t2.查询成绩                            |\n";
    cout << "|\t\t3.统计平时分                          |\n";
    cout << "|\t\t4.作业统计                            |\n";
    cout << "|\t\t5.删除成绩                            |\n";
    cout << "|\t\t6.修改成绩                            |\n";
    cout << "|\t\t7.自动排名                            |\n";
    cout << "|\t\t0.保存退出                            |\n";
    cout << "|-----------------------------------------------------|\n";

    cout << "请输入对应的数字进行操作:";

    while (1)
    {
        
        int x; cin >> x;
        switch (x)
        {
        case 1:
            cjmenu();
            break;
        case 2:
            cxcj();
            break;
        case 3:
            tjpjf();
            break;
        case 4:
            zytj();
            break;
        case 5:
            sccj();
            break;
        case 6:
            xgcj();
            break;
        case 7:
            zdpm();
            break;
        case 0:
            bcbtc();
            exit(0);
        default:
            cout << "无效输入\n";
            break;
        }
    }
}



//保存并退出
void bcbtc() 
{
    //打开文件（没有就先创建）清空后写入
    FILE* fp;
    fp = fopen("cj.txt", "w");

    if (fp == NULL)
    {
        cout << "打开文件失败\n";
        return;
    }

    //遍历链表
    Node* p = g_phead;
    while (p != NULL)
    {
        fwrite(&p->stu, 1, sizeof(Student), fp);
        p = p->pnext;
    }


    //关闭文件
    fclose(fp);

    cout << "请稍候...\n";
    Sleep(2000);
    cout << "数据保存成功!\n";
    Sleep(2000);
}

void cjmenu() 
{
    system("cls");
    cout << "|-----------------------------------------------------|\n";
    cout << "|欢迎使用学生成绩管理系统                             |\n";
    cout << "|-----------------------------------------------------|\n";
    cout << "|请选择输入方式:                                      |\n";
    cout << "|\t\t1.手动输入                            |\n";
    cout << "|\t\t2.文件导入                            |\n";
    cout << "|\t\t3.返回上级                            |\n";
    cout << "|-----------------------------------------------------|\n";
    cout << "请输入对应数字进行操作:";

    while (1) 
    {
        int x; cin >> x;
        switch (x)
        {
        case 1:
            sdsr();
            break;
        case 2:
            wjdr();
            break;
        case 3:
            menu();
            break;

        }
    }
}//1.0成绩菜单




//1.1手动输入
void sdsr()
{
    cout << "需要录入的学生人数:";
    int n; cin >> n;

    for (int i = 0; i < n; i++)
    {
        //创建节点
        Node* pNewnode = (Node*)malloc(sizeof(Node));
        pNewnode->pnext = NULL;

        //头插法
        if (g_phead == NULL)
        {
            g_phead = pNewnode;
        }

        else
        {
            pNewnode->pnext = g_phead;
            g_phead = pNewnode;
        }



        cout << "请输入学生姓名:";
        cin >> pNewnode->stu.name;
        cout << "请输入学生学号:";
        cin >> pNewnode->stu.snum;
        cout << "请输入学生第一次作业完成情况:";
        cin >> pNewnode->stu.zuoye[0];
        cout << "请输入学生第二次作业完成情况:";
        cin >> pNewnode->stu.zuoye[1];
        cout << "请输入学生第三次作业完成情况:";
        cin >> pNewnode->stu.zuoye[2];
        pNewnode->stu.rank = 0;
        pNewnode->stu.score = 0;
        
        cout << "学生信息录入成功!\n";
    }
    system("pause");
    menu();

}



//1.2文件导入
void wjdr()
{
    //打开文件
    FILE* fp = fopen("cj.txt", "r");
    if (fp == NULL)
    {
        cout << "读取文件失败，请检查后重试\n";
        return;
    }

    //读取文件
    Student stu;//先读

    while (fread(&stu, 1, sizeof(Student), fp))//能读就说明读成功了再进行下一步操作,避免乱码
    {
        //创建链表新节点 
        Node* pNewnode = (Node*)malloc(sizeof(Node));
        pNewnode->pnext = NULL;
        memcpy(pNewnode, &stu, sizeof(Student));//复制


        //头插法
        if (g_phead == NULL)
        {
            g_phead = pNewnode;
        }

        else
        {
            pNewnode->pnext = g_phead;
            g_phead = pNewnode;
        }
    }


    //关闭文件
    fclose(fp);
    cout << "加载数据成功，请输入数字继续操作:";
}


void cxcj() 
{
    system("cls");
    printf("*************************************************************************************************\n");
    printf("*\t学号\t姓名\t第一次作业\t第二次作业\t第三次作业\t平时分\t\t排名\t*\n");

    //遍历链表
    Node* p = g_phead;
    while (p != NULL)
    {
        printf("*\t%d\t%s\t%d\t\t%d\t\t%d\t\t%.2lf\t\t%d\t*\n",
            p->stu.snum,
            p->stu.name,
            p->stu.zuoye[0],
            p->stu.zuoye[1],
            p->stu.zuoye[2],
            p->stu.score,
            p->stu.rank);
        p = p->pnext;
    }
    system("pause");
    menu();
}//2.查询成绩


void tjpjf() 
{

    //遍历链表
    Node* p = g_phead;
    
    if (p == NULL)
    {
        cout << "请先录入学生成绩!\n";
        return;
    }

    cout << "请输入每次小测的权重:";
    int quan[3] = {0};
    cout << "第一次小测:";
    cin >> quan[0];
    cout << "第二次小测:";
    cin >> quan[1];
    cout << "第三次小测:";
    cin >> quan[2];

    while (p != NULL)
    {
        p->stu.score = (static_cast<double>(p->stu.zuoye[0]) * quan[0] + p->stu.zuoye[1] * quan[1] + p->stu.zuoye[2] * quan[2]) / (quan[0] + quan[1] + quan[2]);
        p = p->pnext;
    }
    cout << "计算完成\n";
    system("pause");
    menu();
}//3.计算平时分分

//4.作业统计
void zytj()
{
    char sign = '*'; //符号
    int n[11] = {0};   //十个分段十分为一个分段
    int N = 0;   //链表节点数

    //遍历链表
    Node* p = g_phead;
    while (p->pnext != NULL)
    {
        N++;
        p = p->pnext;
    }

    if (p != NULL)
    {
        N++;
    }

    //遍历链表统计分数
    p = g_phead;
    int x;
    for (int i = 0; i < N; i++)
    {
        x = p->stu.score;
        n[(x / 10)]++;
        p = p->pnext;
    }

    //打印字符
    cout << "  |-------------------------------------------------------|\n";
    for (int j = 15; j >= 0; j--)
    {
        if ((j * 5) % 25 == 0)//每五分一个*
        {
            if (j * 5 > 10)
            {
                printf("%d|", j * 5);
            }
            else
            {
                printf(" %d|", j * 5);
            }
        }
        else
        {
            printf("  |");
        }
        for (int i = 0; i < 11; i++)
        {
            if (n[i] > j * 5)
            {
                cout << "  *  ";
            }
            else
            {
                cout << "     ";
            }
        }
        cout << "|" << endl;
    }
    cout << "  |  0   10   20   30   40   50   60   70   80   90   100 |\n";
    system("pause");
    menu();
}


//5.删除成绩
void sccj() 
{
    system("cls");
    cout << "|-----------------------------------------------------|\n";
    cout << "|请选择删除方式:                                      |\n";
    cout << "|\t\t1.按姓名删除                          |\n";
    cout << "|\t\t2.按学号删除                          |\n";
    cout << "|\t\t3.返回上级                            |\n";
    cout << "|-----------------------------------------------------|\n";
    cout << "请输入对应数字进行操作:";
    
    while (1)
    {
        int x; cin >> x;
        switch (x)
        {


        case 1:
            cout << "请输入学生姓名:";
            char fname[20]; cin >> fname;
            cout << "正在删除请稍后\n";
            amzsc(fname);
            cout << "删除成功！请继续操作";
            break;
        case 2:
            cout << "请输入学生学号：";
            int fnum; cin >> fnum;
            cout << "正在删除请稍后\n";
            axhsc(fnum);
            cout << "删除成功！请继续操作";
            break;
        case 3:
            menu();
            break;
        }
    }
}

//5.1按名字删除
void amzsc(char fname[20])
{

    //备份
    Node* p1;
    Node* p = g_phead;
    Node* p2;


    //判断是不是头节点
    if (strcmp(g_phead->stu.name, fname) == 0)
    {
        p1 = g_phead;
        g_phead = g_phead->pnext;//换头


        //删除
        free(p1);
        return;
    }

    //不是头节点
    while (p->pnext != NULL)
    {
        if (strcmp(p->pnext->stu.name, fname) == 0)
        {
            p2 = p->pnext;
            p->pnext = p->pnext->pnext;//链接

            //删除
            free(p2);
            return;
        }
        //遍历
        p = p->pnext;

        if (p->pnext == NULL)
        {
            break;
        }
        
    }

    if (p->pnext == NULL)
    {
        cout << "未找到该学生,按任意键回到上级页面\n";
        system("pause");
        sccj();
    }
}



//5.2按学号删除 
void axhsc(int fnum)
{
    //备份
    Node* p1;
    Node* p = g_phead;
    Node* p2;


    //判断是不是头节点
    if (g_phead->stu.snum == fnum)
    {
        p1 = g_phead;
        g_phead = g_phead->pnext;//换头


        //删除
        free(p1);
        return;
    }

    //不是头节点
    
    while (p->pnext != NULL)
    {
        if (p->pnext->stu.snum == fnum)
        {
            p2 = p->pnext;
            p->pnext = p->pnext->pnext;//链接

            //删除
            free(p2);
            return;
        }
        //遍历
        p = p->pnext;

        if (p->pnext == NULL)
        {
            break;
        }
    }
    if(p->pnext == NULL)
    {
        cout << "未找到该学生,按任意键回到上级页面\n";
        system("pause");
        sccj();
    }

}




//6.0修改成绩
void xgcj()
{
    system("cls");
    cout << "|-----------------------------------------------------|\n";
    cout << "|欢迎使用学生成绩管理系统                             |\n";
    cout << "|-----------------------------------------------------|\n";
    cout << "|请选择输入方式:                                      |\n";
    cout << "|\t\t1.学号查找                            |\n";
    cout << "|\t\t2.姓名查找                            |\n";
    cout << "|\t\t3.返回上级                            |\n";
    cout << "|-----------------------------------------------------|\n";

    cout << "请输入对应数字进行操作:";
    while (1)
    {
        int x; cin >> x;
        switch (x)
        {
        case 1:
            xhcz();
            break;
        case 2:
            xmcz();
            break;
        case 3:
            menu();
            break;

        }
    }
}


//6.1学号查找
void xhcz()
{
    int x;
    cout << "请输入需要修改的学生学号:";
    cin >> x;
    
    //遍历链表
    Node* find = NULL;
    Node* p = g_phead;
    while (p != NULL)
    {
        if (p->stu.snum == x)
        {
            find = p;
            break;
        }
        p = p->pnext;
    }

    if (find != NULL)
    {
        cout << "已成功查找学生信息!\n";


        printf("*\t学号\t姓名\t第一次作业\t第二次作业\t第三次作业\t平时分\t\t排名\t*\n");
        printf("*\t%d\t%s\t%d\t\t%d\t\t%d\t\t%.2lf\t\t%d\t*\n",
            p->stu.snum,
            p->stu.name,
            p->stu.zuoye[0],
            p->stu.zuoye[1],
            p->stu.zuoye[2],
            p->stu.score,
            p->stu.rank);


        system("pause");
        //修改信息
        xg(p);

    }

    else
    {
        cout << "未查询到该学生信息，请检查后再试！";
        system("pause");
        menu();
    }
}


//6.2姓名查找
void xmcz()
{
    char cjname[20];
    cout << "请输入需要修改的学生姓名:";
    cin >> cjname;

    //遍历链表
    Node* find = NULL;
    Node* p = g_phead;
    while (p != NULL)
    {
        //字符串比较函数
        if(strcmp(p->stu.name ,cjname) == 0)
        {
            find = p;
            break;
        }
        p = p->pnext;
    }

    if (find != NULL)
    {
        cout << "已成功查找学生信息!\n";
   
        printf("*\t学号\t姓名\t第一次作业\t第二次作业\t第三次作业\t平时分\t\t排名\t*\n");
        printf("*\t%d\t%s\t%d\t\t%d\t\t%d\t\t%.2lf\t\t%d\t*\n",
            p->stu.snum,
            p->stu.name,
            p->stu.zuoye[0],
            p->stu.zuoye[1],
            p->stu.zuoye[2],
            p->stu.score,
            p->stu.rank);


        system("pause");
        //修改信息
        xg(p);
    }

    else
    {
        cout << "未查询到该学生信息，请检查后再试！";
        system("pause");
        menu();
    }
}

//6.3找到后修改
void xg(Node* p)
{
    int m = 1;
    cout << "请输入数字使用功能:\n";
    cout << "|-----------------------------------------------------|\n";
    cout << "|\t\t0.取消修改,返回主菜单                 |\n";
    cout << "|\t\t1.修改学号                            |\n";
    cout << "|\t\t2.修改姓名                            |\n";
    cout << "|\t\t3.修改第一次成绩                      |\n";
    cout << "|\t\t4.修改第二次成绩                      |\n";
    cout << "|\t\t5.修改第三次成绩                      |\n";
    cout << "|\t\t6.修改平时分                          |\n";
    cout << "|-----------------------------------------------------|\n";

    while (m == 1)
    {
        int num; cin >> num;
        switch (num)
        {
        case 0:
            menu();
            break;
        case 1:
            cout << "请输入修改后的学号:";
            cin >> p->stu.snum;
            break;
        case 2:
            cout << "请输入修改后的姓名:";
            cin >> p->stu.name;
            break;
        case 3:
            cout << "请输入修改后的第一次成绩:";
            cin >> p->stu.zuoye[0];
            break;
        case 4:
            cout << "请输入修改后的第二次成绩:";
            cin >> p->stu.zuoye[1];
            break;
        case 5:
            cout << "请输入修改后的第三次成绩:";
            cin >> p->stu.zuoye[2];
            break;
        case 6:
            cout << "请输入修改后的平时分:";
            cin >> p->stu.score;
            break;
        }
        cout << "修改成功!\n";
        system("pause");
        cout << "继续修改请按1：";
        cin >> m;
    }
    cout << "返回主菜单中！";
    Sleep(2000);
    menu();
}


//自动排名并重排链表
void zdpm()
{
    int N = 0;   //链表节点数
    Node* p = g_phead;   
    
    //遍历链表
    while (p->pnext != NULL)
    {
        N++;
        p = p->pnext;
    }

    if (p != NULL)
    {
        N++;
    }


    Student temp;//中转

    //遍历N-1轮
    for (int i = N - 1; i >= 0; i--)
    {
        p = g_phead;
        for (int j = 0; j < i; j++)
        {
            if (p->stu.score < p->pnext->stu.score)
            {
                temp = p->pnext->stu;
                p->pnext->stu = p->stu;
                p->stu = temp;
            }
            p = p->pnext;//遍历
        }
    }

    //赋排名
    p = g_phead;
    for (int i = 0; i < N; i++)
    {
        p->stu.rank = i + 1;
        p = p->pnext;
    }
    cout << "排名完成\n";
    system("pause");
    menu();
}