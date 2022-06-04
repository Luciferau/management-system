#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "tablePrint.h"
 
struct student {
	int num; //ѧ�� 
	char name[16];
	int cLang; //C ����
	int algo; //�㷨 
	int database; //���ݿ� 
	int sum;
};
int currentCount = 0;
struct student inputInfo()
{ //���Ż���ʹ��ָ�����
	struct student s;
	rewind(stdin); //������뻺���� 
	printf("ѧ��:");
	scanf("%d", &s.num);
	printf("����:");
	scanf("%s", s.name);
	printf("C ����:");
	scanf("%d", &s.cLang);
	printf("�㷨:");
	scanf("%d", &s.algo);
	printf("���ݿ�:");
	scanf("%d", &s.database);
	s.sum = s.cLang + s.algo + s.database; return s;
}
// ��ͷ��Ϣ
char head[][COL_LEN_MAX] = { "ѧ��", "����", "C ����", "�㷨", "���ݿ�", "�ܷ�" };

struct student stu[MAX_COUNT];



void total()
{
	system("cls");
	printf("ͳ��...\n");
}

void order() {
	if (currentCount == 0)
	{
		printf("��û��ѧ����¼��\n");
		return;
	}
	for (int i = 0; i < currentCount - 1; i++)
	{
		for (int j = i + 1; j < currentCount; j++)
		{
			if (stu[i].sum < stu[j].sum)
			{
				struct student t = stu[i];
				stu[i] = stu[j];
				stu[j] = t;
			}
		}
	}
	if (!save())
	{
		printf("����󣬱����ļ�ʧ�ܣ�\n");
	}
	else { show(); }
}

void waitConfirm()
{
	rewind(stdin); //flush(stdin)�� VS2015 ������Ч��ʹ�� rewind����ջ��� getch(); }
}

void showPage(int startIndex, int endIndex)
{
	if (endIndex >= currentCount)
	{
		endIndex = currentCount - 1;
	}
	if (endIndex - startIndex + 1 > RECORDER_PER_PAGE)
	{
		endIndex = startIndex + RECORDER_PER_PAGE - 1;
	}
	char row[6][COL_LEN_MAX];
	system("cls");
	printTableHead(TABLE_WIDTH, 6);
	printTableRow(TABLE_WIDTH, head, sizeof(head) / sizeof(head[0]));
	printTableMidLine(TABLE_WIDTH, 6);
	for (int i = startIndex; i <= endIndex; i++)
	{
		sprintf(row[0], "%d", stu[i].num);
		sprintf(row[1], "%s", stu[i].name);
		sprintf(row[2], "%d", stu[i].cLang);
		sprintf(row[3], "%d", stu[i].algo);
		sprintf(row[4], "%d", stu[i].database);
		sprintf(row[5], "%d", stu[i].sum);
		printTableRow(TABLE_WIDTH, row, 6);
		if (i < endIndex)
		{
			printTableMidLine(TABLE_WIDTH, 6);
		}
		else
		{
			printTableTail(TABLE_WIDTH, 6);
		}
	}
}

void show() {
	system("cls");
	if (currentCount == 0)
	{
		printf("��û��ѧ����Ϣ��\n");
		return;
	}
	int pageCount = (currentCount + RECORDER_PER_PAGE - 1) / RECORDER_PER_PAGE;
	char buff[64];
	for (int i = 0; i < pageCount; i++)
	{
		showPage(i * RECORDER_PER_PAGE, (i + 1) * RECORDER_PER_PAGE - 1);
		sprintf(buff, "��%d ҳ ��[%d]ҳ", pageCount, i + 1);
		printMidInfo(buff);
		if (i < pageCount - 1)
		{
			waitConfirm();
		}
	}
}

bool save() {
	FILE* fp = fopen("data.txt", "wb");
	if (fp == NULL)
	{
		fclose(fp);
		return false;
	}
	for (int i = 0; i < currentCount; i++)
	{
		if (fwrite(&stu[i], sizeof(struct student), 1, fp) != 1)
		{
			fclose(fp);
			return false;
		}
	}fclose(fp);
	return true;
}

void input() {
	char str[16];
	struct student s;
	menu();
	while (1)
	{
		system("cls");
		printf("����ѧ����Ϣ(y/n):");
		rewind(stdin);
		//������뻺���� 
		scanf("%s", str);
		if (strcmp(str, "Y") != 0 && strcmp(str, "y") != 0)
		{
			break;
		}
		s = inputInfo();
		if (searchStu(s.num) >= 0)
		{
			printf("ѧ��[%d] �Ѿ����ڣ�\n", s.num);
			waitConfirm();
			continue;
		}
		stu[currentCount++] = s;
		if (!save())
		{
			printf("����ʧ�ܣ�\n");

		}
		else
		{
			printf("����ɹ���\n");
		}
		waitConfirm();
	}printf("\n ��������!\n");
}

void search() {
	int snum = 0;
	system("cls");
	printf("������ѧ��:");
	scanf("%d", &snum);
	int i = searchStu(snum);
	if (i < 0)
	{
		printf("û���ҵ�����ѧ����\n");
		return;
	}
	char row[6][COL_LEN_MAX];
	char head[][COL_LEN_MAX] = { "ѧ��", "����", "C ����", "�㷨", "���ݿ�", "�ܷ�" };
	printTableHead(TABLE_WIDTH, 6);
	printTableRow(TABLE_WIDTH, head, sizeof(head) / sizeof(head[0]));

	printTableMidLine(TABLE_WIDTH, 6);
	sprintf(row[0], "%d", stu[i].num);
	sprintf(row[1], "%s", stu[i].name);
	sprintf(row[2], "%d", stu[i].cLang);
	sprintf(row[3], "%d", stu[i].algo);
	sprintf(row[4], "%d", stu[i].database);
	sprintf(row[5], "%d", stu[i].sum);
	printTableRow(TABLE_WIDTH, row, 6);
	printTableTail(TABLE_WIDTH, 6);
}

void del()
{
	FILE* fp;
	int snum = 0;
	char str[16] = "";
	system("cls");
	printf("������ѧ��:");
	scanf("%d", &snum);
	int i = searchStu(snum);
	if (i < 0)
	{
		printf("û���ҵ�����ѧ��!\n");
		return;
	}
	printf("�ҵ�������¼���Ƿ�ɾ����(y/n)");
	scanf("%s", str);
	if (strcmp(str, "Y") == 0 || strcmp(str, "y") == 0)
	{
		for (int j = i; j < currentCount; j++)
		{
			stu[j] = stu[j + 1];
		}
		currentCount--;
		if (save())
		{
			printf("ɾ���ɹ���\n");
		}
		else {
			printf("�����ļ�ʧ�ܣ�\n");
		}
	}
	else { printf("ȡ��ɾ����\n"); }
}

void modify()
{
	int snum;
	system("cls");
	printf("������Ҫ�޸ĵ�ѧ����ѧ��: ");
	scanf("%d", &snum);
	int i = searchStu(snum);
	if (i < 0)
	{
		printf("û���ҵ�����ѧ��!\n");
		return;
	}
	printf("�ҵ�������ѧ��, �����޸�������Ϣ��\n");
	printf("����:");
	scanf("%s", stu[i].name);
	printf("C ����:");
	scanf("%d", &stu[i].cLang);
	printf("�㷨:");

	scanf("%d", &stu[i].algo);
	printf("���ݿ�:");
	scanf("%d", &stu[i].database);
	stu[i].sum = stu[i].cLang + stu[i].algo + stu[i].database;
	if (save())
	{
		printf("�޸ĳɹ���\n");
	}
	else
	{
		printf("�����ļ�ʧ�ܣ�\n");
	}

}

void insert() {
	int snum;
	system("cls");
	printf("������Ҫ�����λ��(ѧ��):");
	scanf("%d", &snum);
	int destIndex = searchStu(snum);
	if (destIndex < 0)
	{
		printf("û������ѧ��������λ�ô���!\n");
		return;
	}
	struct student t = inputInfo();
	int i = searchStu(t.num);
	if (i >= 0)
	{
		printf("ѧ��[%d]�Ѿ�����! \n", t.num);
		return;
	}
	for (int j = currentCount - 1; j > destIndex; j--)
	{
		stu[j + 1] = stu[j];
	}
	stu[destIndex + 1] = t;
	currentCount++;
	if (save())
	{
		printf("����ɹ���\n");
	}
	else {
		printf("�����ļ�ʧ�ܣ�\n");
	}
}

int searchStu(int snum)
{
	for (int i = 0; i < currentCount; i++)
	{
		if (stu[i].num == snum)
		{
			return i;
		}
	}return -1;
}


void menu() {
	system("cls");
	printTableHead(MENU_WIDTH); 
	printTableMidInfo(MENU_WIDTH, "ѧ����Ϣ����ϵͳ");
	printTableMidInfo(MENU_WIDTH, "");
	const char* subMenus[] = { "1. ����ѧ����Ϣ", "2. ����ѧ����Ϣ", "3. ɾ��ѧ����Ϣ", "4. �޸�ѧ����Ϣ", "5. ����ѧ����Ϣ", "6. ѧ���ɼ�����", "7. ͳ��ѧ������", "8. ��ʾ������Ϣ", "0. �˳�ϵͳ " }; 
	int count = sizeof(subMenus) / sizeof(subMenus[0]);
	for (int i = 0; i < count; i++) 
	{ 
		printTableMidInfo(MENU_WIDTH, subMenus[i]);
	}
	printTableMidInfo(MENU_WIDTH, "");
	printTableTail(MENU_WIDTH);
	printMidInfo("��ѡ��(0-8): ");
}

void init() 
{	//���ÿ���̨����
	char cmd[1024]; 
	sprintf(cmd, "mode con lines=%d cols=%d", WIN_HEIGHT, WIN_WIDTH);//���ַ�������cmd������һ������
	system(cmd); 
	system("color f0"); //system("color f0\n");
	memset(stu, 0, sizeof(stu));
	FILE* fp = fopen("data.txt", "rb");
	if (fp == NULL) 
	{  printf("�ļ�������!\n");
		currentCount = 0;
		return;
	}
	int i = 0; 
	while (!feof(fp)) { 
		int ret = fread(&stu[i], sizeof(struct student), 1, fp);
		if (ret == 1)
		{
			i++; 
		}
	}
	currentCount = i;
	menu();
}



 


 

int main(void)
{
	init();
	menu();
	int n;
	scanf("%d", &n); 
	while (1) {
		switch (n) 
		{
		case 1:
			input();
			break;
		case 2:
			search();
			break;
		case 3:
			del();
			break;
		case 4:
			modify();
			break;
		case 5:
			insert();
			break;
		case 6:
			order();
			break;
		case 7:
			total();
			break;
		case 8:
			show();
			break;
		default:break;
		}
		waitConfirm();
	
		menu();
		rewind(stdin); // fflush(stdin)���� VS2015 ������Ч 
		scanf("%d", &n);
	}
		 
		return 0;

}