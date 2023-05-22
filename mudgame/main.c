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

	int cols = 80, lines = 30;
	// 초기 화면 설정
	system("mode con: cols=80 lines=30");  //cols = 칸/행 (가로)  lines = 줄/열 (세로)
	SetConsoleTitle(TEXT("Last Choice"));
	CursorView(false);
	
	// 메뉴 선택
	int cursor_loc = -1;
	int* pCL = &cursor_loc;
	int start = 0;
	int* pS = &start;

	//PrintfText("map.txt", 10, 5);
	PrintMap();
	/*
	
	DrawLines(cols, lines);
	DrawStart(cols, lines, pCL, pS);

	// 게임 시작
	DrawLines(cols, lines);

	// 아이템 선택 - 각 장소에 랜덤으로 아이템 배정
	ItemRandom();
	// 60초 동안 아이템 선택
	//TimeCount(60);

	ItemChoice(cols, lines);
	//printf("선택이 종료되었습니다.\n");

	// 방공호에서 10일





	//게임 끝
	//printf_txt("logo.txt"); //로고 출력
	*/
}


