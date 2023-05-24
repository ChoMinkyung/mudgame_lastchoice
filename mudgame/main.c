#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include<conio.h>
#include <process.h>
#include <Windows.h>
#include "func.h"



int main()
{
	what Item;
	where place = LIVING_ROOM;

	int cols = 80, lines = 40;
	// 초기 화면 설정
	system("mode con: cols=80 lines=40");  //cols = 칸/행 (가로)  lines = 줄/열 (세로)
	SetConsoleTitle(TEXT("Last Choice"));
	CursorView(false);

	// 메뉴 선택
	int cursor_loc = -1;
	int* pCL = &cursor_loc;
	int start = 0;
	int* pS = &start;
	int hp = 5;
	int* pHp = &hp;

	
	/*
	DrawLines(cols, lines);
	DrawStart(cols, lines, pCL, pS, 5);

	// 게임 시작
	DrawLines(cols, lines);

	// 아이템 선택 - 각 장소에 랜덤으로 아이템 배정
	ItemRandom();

	// 60초 동안 아이템 선택
	ItemChoice(cols, lines, 5);

	// 방공호에서 10일
	ShelterPage(cols, lines, pHp);
	system("cls");
	
	*/
	//게임 끝
	if (hp == 0)
	{
		PrintfText("lose.txt", cols, lines); //로고 출력
		gotoxy(30, 35);
		printf("당신[렉스]은 죽었습니다.");
		Sleep(500000);
	}
	else
	{
		PrintfText("win.txt", cols, lines); //로고 출력
		gotoxy(25, 25);
		printf("축하합니다. 생존에 성공했습니다.");
		Sleep(500000);
	}

}


