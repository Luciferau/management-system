#pragma once

// 窗口宽度
#define WIN_WIDTH 80
// 窗口高度
#define WIN_HEIGHT 25

#define TABLE_WIDTH 78
#define RECORDER_PER_PAGE 10
#define MAX_COUNT 1000
#define MENU_WIDTH  50
#define COL_LEN_MAX 64


void menu();
void init();
void input();
void search();
void del();
void modify();
void insert();
void order();
void total();
void waitConfirm();
void showPage(int startIndex, int endIndex);
void show();
bool save();
int searchStu(int snum);
void printTableHead(int tableWidth);
void printTableTail(int tableWidth);
void printTableRow(int tableWidth, char cols[][COL_LEN_MAX], int n);
void printTableHead(int tableWidth, int cols);
void printTableTail(int tableWidth, int cols);
void printTableMidLine(int tableWidth, int cols);
void printTableMidInfo(int tableWidth, const char* str);
void printMidInfo(const char* str);