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

	// 시작 페이지
	system("mode con cols=92 lines=40");  //cols = 칸/행 (가로)  lines = 줄/열 (세로)
	gotoxy(myX, myY);
	
	printF("출력\n");
	printf("\n\n\n");
	printF();

	// 아이템 챙기기 60초 카운트

	// 방공호에서 10일
}