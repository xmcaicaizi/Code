//ͷ�ļ�
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<stdio.h>
#include <iostream>
#include<string.h>
using namespace std;



//�ṹ������
typedef struct _Student
{
    char name[20];//ѧ������
    int snum;//ѧ��
    int zuoye[3];//��ҵ������
    double score;//ƽʱ��
    int rank;//����
}Student;


//�ڵ�
typedef struct _Node {
    Student stu;//ѧ��
    struct _Node* pnext;//ָ����һ���ڵ��ָ��
}Node;


//ͷ�ڵ�
Node* g_phead = NULL;//ʲô��û��,��


//��������
void menu();//��ʼ����
void cjmenu();//1.0�ɼ��˵�
void sdsr();//1.1�ֶ�����
void wjdr();//1.2�ļ�����
void cxcj();//2.��ѯ�ɼ�
void tjpjf();//3.ͳ��ƽʱ���
void zytj();//4.��ҵͳ��
void sccj();//5.ɾ���ɼ�
void amzsc(char fname[20]);//5.1������ɾ��
void axhsc(int fnum);//5.2��ѧ��ɾ��
void xgcj();//6.�޸ĳɼ�
void xhcz();//6.1ѧ�Ų���
void xmcz();//6.2��������
void xg(Node* p);//6.3�ҵ����޸�
void zdpm();//7�Զ�����
void bcbtc();//0.���沢�˳�





int main()
{
    menu();
}


//��ʼ�˵�
void menu()
{
    system("cls");
    cout << "|-----------------------------------------------------|\n";
    cout << "|��ӭʹ��ѧ���ɼ�����ϵͳ                             |\n";
    cout << "|-----------------------------------------------------|\n";
    cout << "|\t\t1.����ɼ�                            |\n";
    cout << "|\t\t2.��ѯ�ɼ�                            |\n";
    cout << "|\t\t3.ͳ��ƽʱ��                          |\n";
    cout << "|\t\t4.��ҵͳ��                            |\n";
    cout << "|\t\t5.ɾ���ɼ�                            |\n";
    cout << "|\t\t6.�޸ĳɼ�                            |\n";
    cout << "|\t\t7.�Զ�����                            |\n";
    cout << "|\t\t0.�����˳�                            |\n";
    cout << "|-----------------------------------------------------|\n";

    cout << "�������Ӧ�����ֽ��в���:";

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
            cout << "��Ч����\n";
            break;
        }
    }
}



//���沢�˳�
void bcbtc() 
{
    //���ļ���û�о��ȴ�������պ�д��
    FILE* fp;
    fp = fopen("cj.txt", "w");

    if (fp == NULL)
    {
        cout << "���ļ�ʧ��\n";
        return;
    }

    //��������
    Node* p = g_phead;
    while (p != NULL)
    {
        fwrite(&p->stu, 1, sizeof(Student), fp);
        p = p->pnext;
    }


    //�ر��ļ�
    fclose(fp);

    cout << "���Ժ�...\n";
    Sleep(2000);
    cout << "���ݱ���ɹ�!\n";
    Sleep(2000);
}

void cjmenu() 
{
    system("cls");
    cout << "|-----------------------------------------------------|\n";
    cout << "|��ӭʹ��ѧ���ɼ�����ϵͳ                             |\n";
    cout << "|-----------------------------------------------------|\n";
    cout << "|��ѡ�����뷽ʽ:                                      |\n";
    cout << "|\t\t1.�ֶ�����                            |\n";
    cout << "|\t\t2.�ļ�����                            |\n";
    cout << "|\t\t3.�����ϼ�                            |\n";
    cout << "|-----------------------------------------------------|\n";
    cout << "�������Ӧ���ֽ��в���:";

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
}//1.0�ɼ��˵�




//1.1�ֶ�����
void sdsr()
{
    cout << "��Ҫ¼���ѧ������:";
    int n; cin >> n;

    for (int i = 0; i < n; i++)
    {
        //�����ڵ�
        Node* pNewnode = (Node*)malloc(sizeof(Node));
        pNewnode->pnext = NULL;

        //ͷ�巨
        if (g_phead == NULL)
        {
            g_phead = pNewnode;
        }

        else
        {
            pNewnode->pnext = g_phead;
            g_phead = pNewnode;
        }



        cout << "������ѧ������:";
        cin >> pNewnode->stu.name;
        cout << "������ѧ��ѧ��:";
        cin >> pNewnode->stu.snum;
        cout << "������ѧ����һ����ҵ������:";
        cin >> pNewnode->stu.zuoye[0];
        cout << "������ѧ���ڶ�����ҵ������:";
        cin >> pNewnode->stu.zuoye[1];
        cout << "������ѧ����������ҵ������:";
        cin >> pNewnode->stu.zuoye[2];
        pNewnode->stu.rank = 0;
        pNewnode->stu.score = 0;
        
        cout << "ѧ����Ϣ¼��ɹ�!\n";
    }
    system("pause");
    menu();

}



//1.2�ļ�����
void wjdr()
{
    //���ļ�
    FILE* fp = fopen("cj.txt", "r");
    if (fp == NULL)
    {
        cout << "��ȡ�ļ�ʧ�ܣ����������\n";
        return;
    }

    //��ȡ�ļ�
    Student stu;//�ȶ�

    while (fread(&stu, 1, sizeof(Student), fp))//�ܶ���˵�����ɹ����ٽ�����һ������,��������
    {
        //���������½ڵ� 
        Node* pNewnode = (Node*)malloc(sizeof(Node));
        pNewnode->pnext = NULL;
        memcpy(pNewnode, &stu, sizeof(Student));//����


        //ͷ�巨
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


    //�ر��ļ�
    fclose(fp);
    cout << "�������ݳɹ������������ּ�������:";
}


void cxcj() 
{
    system("cls");
    printf("*************************************************************************************************\n");
    printf("*\tѧ��\t����\t��һ����ҵ\t�ڶ�����ҵ\t��������ҵ\tƽʱ��\t\t����\t*\n");

    //��������
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
}//2.��ѯ�ɼ�


void tjpjf() 
{

    //��������
    Node* p = g_phead;
    
    if (p == NULL)
    {
        cout << "����¼��ѧ���ɼ�!\n";
        return;
    }

    cout << "������ÿ��С���Ȩ��:";
    int quan[3] = {0};
    cout << "��һ��С��:";
    cin >> quan[0];
    cout << "�ڶ���С��:";
    cin >> quan[1];
    cout << "������С��:";
    cin >> quan[2];

    while (p != NULL)
    {
        p->stu.score = (static_cast<double>(p->stu.zuoye[0]) * quan[0] + p->stu.zuoye[1] * quan[1] + p->stu.zuoye[2] * quan[2]) / (quan[0] + quan[1] + quan[2]);
        p = p->pnext;
    }
    cout << "�������\n";
    system("pause");
    menu();
}//3.����ƽʱ�ַ�

//4.��ҵͳ��
void zytj()
{
    char sign = '*'; //����
    int n[11] = {0};   //ʮ���ֶ�ʮ��Ϊһ���ֶ�
    int N = 0;   //����ڵ���

    //��������
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

    //��������ͳ�Ʒ���
    p = g_phead;
    int x;
    for (int i = 0; i < N; i++)
    {
        x = p->stu.score;
        n[(x / 10)]++;
        p = p->pnext;
    }

    //��ӡ�ַ�
    cout << "  |-------------------------------------------------------|\n";
    for (int j = 15; j >= 0; j--)
    {
        if ((j * 5) % 25 == 0)//ÿ���һ��*
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


//5.ɾ���ɼ�
void sccj() 
{
    system("cls");
    cout << "|-----------------------------------------------------|\n";
    cout << "|��ѡ��ɾ����ʽ:                                      |\n";
    cout << "|\t\t1.������ɾ��                          |\n";
    cout << "|\t\t2.��ѧ��ɾ��                          |\n";
    cout << "|\t\t3.�����ϼ�                            |\n";
    cout << "|-----------------------------------------------------|\n";
    cout << "�������Ӧ���ֽ��в���:";
    
    while (1)
    {
        int x; cin >> x;
        switch (x)
        {


        case 1:
            cout << "������ѧ������:";
            char fname[20]; cin >> fname;
            cout << "����ɾ�����Ժ�\n";
            amzsc(fname);
            cout << "ɾ���ɹ������������";
            break;
        case 2:
            cout << "������ѧ��ѧ�ţ�";
            int fnum; cin >> fnum;
            cout << "����ɾ�����Ժ�\n";
            axhsc(fnum);
            cout << "ɾ���ɹ������������";
            break;
        case 3:
            menu();
            break;
        }
    }
}

//5.1������ɾ��
void amzsc(char fname[20])
{

    //����
    Node* p1;
    Node* p = g_phead;
    Node* p2;


    //�ж��ǲ���ͷ�ڵ�
    if (strcmp(g_phead->stu.name, fname) == 0)
    {
        p1 = g_phead;
        g_phead = g_phead->pnext;//��ͷ


        //ɾ��
        free(p1);
        return;
    }

    //����ͷ�ڵ�
    while (p->pnext != NULL)
    {
        if (strcmp(p->pnext->stu.name, fname) == 0)
        {
            p2 = p->pnext;
            p->pnext = p->pnext->pnext;//����

            //ɾ��
            free(p2);
            return;
        }
        //����
        p = p->pnext;

        if (p->pnext == NULL)
        {
            break;
        }
        
    }

    if (p->pnext == NULL)
    {
        cout << "δ�ҵ���ѧ��,��������ص��ϼ�ҳ��\n";
        system("pause");
        sccj();
    }
}



//5.2��ѧ��ɾ�� 
void axhsc(int fnum)
{
    //����
    Node* p1;
    Node* p = g_phead;
    Node* p2;


    //�ж��ǲ���ͷ�ڵ�
    if (g_phead->stu.snum == fnum)
    {
        p1 = g_phead;
        g_phead = g_phead->pnext;//��ͷ


        //ɾ��
        free(p1);
        return;
    }

    //����ͷ�ڵ�
    
    while (p->pnext != NULL)
    {
        if (p->pnext->stu.snum == fnum)
        {
            p2 = p->pnext;
            p->pnext = p->pnext->pnext;//����

            //ɾ��
            free(p2);
            return;
        }
        //����
        p = p->pnext;

        if (p->pnext == NULL)
        {
            break;
        }
    }
    if(p->pnext == NULL)
    {
        cout << "δ�ҵ���ѧ��,��������ص��ϼ�ҳ��\n";
        system("pause");
        sccj();
    }

}




//6.0�޸ĳɼ�
void xgcj()
{
    system("cls");
    cout << "|-----------------------------------------------------|\n";
    cout << "|��ӭʹ��ѧ���ɼ�����ϵͳ                             |\n";
    cout << "|-----------------------------------------------------|\n";
    cout << "|��ѡ�����뷽ʽ:                                      |\n";
    cout << "|\t\t1.ѧ�Ų���                            |\n";
    cout << "|\t\t2.��������                            |\n";
    cout << "|\t\t3.�����ϼ�                            |\n";
    cout << "|-----------------------------------------------------|\n";

    cout << "�������Ӧ���ֽ��в���:";
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


//6.1ѧ�Ų���
void xhcz()
{
    int x;
    cout << "��������Ҫ�޸ĵ�ѧ��ѧ��:";
    cin >> x;
    
    //��������
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
        cout << "�ѳɹ�����ѧ����Ϣ!\n";


        printf("*\tѧ��\t����\t��һ����ҵ\t�ڶ�����ҵ\t��������ҵ\tƽʱ��\t\t����\t*\n");
        printf("*\t%d\t%s\t%d\t\t%d\t\t%d\t\t%.2lf\t\t%d\t*\n",
            p->stu.snum,
            p->stu.name,
            p->stu.zuoye[0],
            p->stu.zuoye[1],
            p->stu.zuoye[2],
            p->stu.score,
            p->stu.rank);


        system("pause");
        //�޸���Ϣ
        xg(p);

    }

    else
    {
        cout << "δ��ѯ����ѧ����Ϣ����������ԣ�";
        system("pause");
        menu();
    }
}


//6.2��������
void xmcz()
{
    char cjname[20];
    cout << "��������Ҫ�޸ĵ�ѧ������:";
    cin >> cjname;

    //��������
    Node* find = NULL;
    Node* p = g_phead;
    while (p != NULL)
    {
        //�ַ����ȽϺ���
        if(strcmp(p->stu.name ,cjname) == 0)
        {
            find = p;
            break;
        }
        p = p->pnext;
    }

    if (find != NULL)
    {
        cout << "�ѳɹ�����ѧ����Ϣ!\n";
   
        printf("*\tѧ��\t����\t��һ����ҵ\t�ڶ�����ҵ\t��������ҵ\tƽʱ��\t\t����\t*\n");
        printf("*\t%d\t%s\t%d\t\t%d\t\t%d\t\t%.2lf\t\t%d\t*\n",
            p->stu.snum,
            p->stu.name,
            p->stu.zuoye[0],
            p->stu.zuoye[1],
            p->stu.zuoye[2],
            p->stu.score,
            p->stu.rank);


        system("pause");
        //�޸���Ϣ
        xg(p);
    }

    else
    {
        cout << "δ��ѯ����ѧ����Ϣ����������ԣ�";
        system("pause");
        menu();
    }
}

//6.3�ҵ����޸�
void xg(Node* p)
{
    int m = 1;
    cout << "����������ʹ�ù���:\n";
    cout << "|-----------------------------------------------------|\n";
    cout << "|\t\t0.ȡ���޸�,�������˵�                 |\n";
    cout << "|\t\t1.�޸�ѧ��                            |\n";
    cout << "|\t\t2.�޸�����                            |\n";
    cout << "|\t\t3.�޸ĵ�һ�γɼ�                      |\n";
    cout << "|\t\t4.�޸ĵڶ��γɼ�                      |\n";
    cout << "|\t\t5.�޸ĵ����γɼ�                      |\n";
    cout << "|\t\t6.�޸�ƽʱ��                          |\n";
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
            cout << "�������޸ĺ��ѧ��:";
            cin >> p->stu.snum;
            break;
        case 2:
            cout << "�������޸ĺ������:";
            cin >> p->stu.name;
            break;
        case 3:
            cout << "�������޸ĺ�ĵ�һ�γɼ�:";
            cin >> p->stu.zuoye[0];
            break;
        case 4:
            cout << "�������޸ĺ�ĵڶ��γɼ�:";
            cin >> p->stu.zuoye[1];
            break;
        case 5:
            cout << "�������޸ĺ�ĵ����γɼ�:";
            cin >> p->stu.zuoye[2];
            break;
        case 6:
            cout << "�������޸ĺ��ƽʱ��:";
            cin >> p->stu.score;
            break;
        }
        cout << "�޸ĳɹ�!\n";
        system("pause");
        cout << "�����޸��밴1��";
        cin >> m;
    }
    cout << "�������˵��У�";
    Sleep(2000);
    menu();
}


//�Զ���������������
void zdpm()
{
    int N = 0;   //����ڵ���
    Node* p = g_phead;   
    
    //��������
    while (p->pnext != NULL)
    {
        N++;
        p = p->pnext;
    }

    if (p != NULL)
    {
        N++;
    }


    Student temp;//��ת

    //����N-1��
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
            p = p->pnext;//����
        }
    }

    //������
    p = g_phead;
    for (int i = 0; i < N; i++)
    {
        p->stu.rank = i + 1;
        p = p->pnext;
    }
    cout << "�������\n";
    system("pause");
    menu();
}