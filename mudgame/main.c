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

	// 초기 화면 설정
	system("mode con: cols=100 lines=30");  //cols = 칸/행 (가로)  lines = 줄/열 (세로)
	SetConsoleTitle(TEXT("Last Choice"));
	CursorView(false);

	// 시작 페이지 출력
	//PrintfText("intro_logo.txt"); //로고 출력
	

	// 각 장소에 랜덤으로 아이템 배정
	ItemRandom();

	// 60초 동안 아이템 선택
	ItemChoice();
	//printf("선택이 종료되었습니다.\n");

	// 방공호에서 10일





	//게임 끝
	//printf_txt("logo.txt"); //로고 출력
}

