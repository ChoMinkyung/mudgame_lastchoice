#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include<conio.h>
#include <Windows.h>

#define COLS 150
#define LINES 50

typedef enum {

}what;

typedef enum {

}where;

void gotoxy(int x, int y);
void printf_txt(char* file_name);
void time_count(int second);
void CursorView(bool show);

int main()
{
	what Item;
	where place;
	int myX = 1, myY = 1;
	CursorView(false);

	// ���� ������ ���
	system("mode con: cols=%d  lines=%d", COLS, LINES);  //cols = ĭ/�� (����)  lines = ��/�� (����)
	SetConsoleTitle(TEXT("Last Choice"));
	//system("cls");
	gotoxy(0, 5);
	printf_txt("intro_logo.txt"); //�ΰ� ���

	//gotoxy(myX, myY);
	//printf("������");

	// ������ ì��� 60�� ī��Ʈ
	
	//gotoxy(5, 5);
	//printf("�̵��� ��Ҹ� ������.\n");
	//printf("1. �Ž� 2. ħ�� 3. �ֹ� 4. ȭ��� 5. ���ȣ\n");
	time_count(60);

	// ���ȣ���� 10��




	//���� ��
	//printf_txt("logo.txt"); //�ΰ� ���
}


// Ŀ�� �̵� �Լ�
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


//txt ���� ��� �Լ�
void printf_txt(char* file_name)
{
	FILE* fp;
	
	char file_path[20] = { "data/" };
	char str[256];
	strcat(file_path, file_name);
	fp = fopen(file_path, "rt");

	//system("mode con cols=200");

	if (fp == NULL)
	{
		printf("����\n");
		exit(1);
	}

	while (fgets(str, 255, fp) != NULL)
	{
		printf(str);
	}
	puts("");

	fclose(fp);
}

// Ÿ�̸� �Լ�
void time_count(int second)
{
	//system("cls");

	while (1)
	{
		gotoxy(COLS-17, 1);
		printf("���� �ð� : %d��\n", second); // x: ��ü-17
		Sleep(1000); // 1�� ����

		gotoxy(COLS - 17, 1);
		printf("                \n");
		second -= 1; // 1�ʾ� ī��Ʈ

		if (second < 0) break;
	}
	
}

// Ŀ�� ������ ON/OFF
void CursorView(bool show)
{
	// show=false ������ ����
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
