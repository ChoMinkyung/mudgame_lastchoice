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

	// 시작 페이지 출력
	system("mode con: cols=%d  lines=%d", COLS, LINES);  //cols = 칸/행 (가로)  lines = 줄/열 (세로)
	SetConsoleTitle(TEXT("Last Choice"));
	//system("cls");
	gotoxy(0, 5);
	printf_txt("intro_logo.txt"); //로고 출력

	//gotoxy(myX, myY);
	//printf("ㅁㅁㅁ");

	// 아이템 챙기기 60초 카운트
	
	//gotoxy(5, 5);
	//printf("이동할 장소를 고르세요.\n");
	//printf("1. 거실 2. 침실 3. 주방 4. 화장실 5. 방공호\n");
	time_count(60);

	// 방공호에서 10일




	//게임 끝
	//printf_txt("logo.txt"); //로고 출력
}


// 커서 이동 함수
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


//txt 파일 출력 함수
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
		printf("실패\n");
		exit(1);
	}

	while (fgets(str, 255, fp) != NULL)
	{
		printf(str);
	}
	puts("");

	fclose(fp);
}

// 타이머 함수
void time_count(int second)
{
	//system("cls");

	while (1)
	{
		gotoxy(COLS-17, 1);
		printf("남은 시간 : %d초\n", second); // x: 전체-17
		Sleep(1000); // 1초 지연

		gotoxy(COLS - 17, 1);
		printf("                \n");
		second -= 1; // 1초씩 카운트

		if (second < 0) break;
	}
	
}

// 커서 깜빡이 ON/OFF
void CursorView(bool show)
{
	// show=false 깜빡임 제거
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
