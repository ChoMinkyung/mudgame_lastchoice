#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>

typedef enum {

}what;

typedef enum {

}where;

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


int main()
{
	what Item;
	where place;
	int myX = 10, myY = 10;

	// ���� ������
	system("mode con cols=92 lines=40");  //cols = ĭ/�� (����)  lines = ��/�� (����)
	gotoxy(myX, myY);
	
	printF("���\n");
	printf("\n\n\n");
	printF();

	// ������ ì��� 60�� ī��Ʈ

	// ���ȣ���� 10��
}