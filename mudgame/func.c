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

int item_list[20] = { 0, 10, 10, 1, 1, 1, 1, 1 , 1, 1, 1, 1, 1, 1, 1 };
int place_item[5][5] = { 0 };
int total_item = 0;
int my_item[20] = { 0 };

// 커서 이동 함수
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//txt 파일 출력 함수
void PrintfText(char* file_name)
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
int TimeCount(int second)
{
	while (1)
	{
		gotoxy(100 - 17, 1);
		printf("남은 시간 : %d초\n", second); // x: 전체-17
		Sleep(1000); // 1초 지연

		gotoxy(100 - 17, 1);
		printf("                \n");
		second -= 1; // 1초씩 카운트

		if (second < 0) break;
	}
	return -1;
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

// Item 출력 함수
int PrintfItem(int place, int item_loc)
{
	switch (place_item[place][item_loc])
	{
	case soup:
		printf("스프");
		break;
	case water:
		printf("물");
		break;
	case map:
		printf("지도");
		break;
	case gas_mask:
		printf("방독면");
		break;
	case radio:
		printf("라디오");
		break;
	case ax:
		printf("도끼");
		break;
	case book:
		printf("책");
		break;
	case checker_board:
		printf("체커보드");
		break;
	case card:
		printf("카드");
		break;
	case gun:
		printf("총");
		break;
	case flashlight:
		printf("손전등");
		break;
	case first_aid_kit:
		printf("구급상자");
		break;
	case bottle:
		printf("물통");
		break;
	case megaphone:
		printf("확성기");
		break;
	case empty:
		break;

	default:
		break;
	}
}

// Place 출력 함수
void PrintfPlace(int place)
{
	switch (place)
	{
	case LIVING_ROOM:
		SetColor(DarkYellow);
		printf("[거실]\n");
		SetColor(WHITE);
		break;
	case BED_ROOM:
		SetColor(DarkYellow);
		printf("[침실]\n");
		SetColor(WHITE);
		break;
	case DIVING_ROOM:
		SetColor(DarkYellow);
		printf("[주방]\n");
		SetColor(WHITE);
		break;
	case BATH_ROOM:
		SetColor(DarkYellow);
		printf("[화장실]\n");
		SetColor(WHITE);
		break;
	case SHELTER:
		SetColor(DarkYellow);
		printf("[방공호]\n");
		SetColor(WHITE);
		break;
	}
}

// Place 에 랜덤으로 Item 넣는 함수
void ItemRandom()
{
	srand(time(NULL));

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int random = rand() % 10 + 1; //1~10사이 수 추출
			if (item_list[random] != 0)
			{
				place_item[i][j] = random;
				item_list[random] -= 1;
			}
			else j--; //다시 뽑기

		}
	}
}

// Place에 있는 Item 출력 함수
void PrintfPlaceItem(where place)
{
	PrintfPlace(place);
	printf("\n");
	int item_loc = 0;
	int n_item = 1;
	printf("0. 돌아가기");
	for (item_loc; item_loc < 5; item_loc++)
	{
		if (place_item[place][item_loc] != 0)
		{
			printf("   %d. ", n_item);
			PrintfItem(place, item_loc);
			n_item++;
		}
	}
	printf("                                       ");
}

// Item이 선택되어서 빈곳이 생겼을 때 앞으로 땡겨주는 함수
void SortZero(where place)
{
	for (int i = 0; i < 4; i++)
	{
		if (place_item[place][i] == 0)
		{
			place_item[place][i] = place_item[place][i + 1];
			place_item[place][i + 1] = 0;
		}
	}
}

// 60초 동안 Item 선택하는 함수
void ItemChoice()
{
	boolean input = true;

	char select_place;
	char select_item;
	clock_t start, end;
	int n_item = 0;
	int* pNitem = &n_item;
	int my_bag[4] = { 0 };
	int* pMybag = my_bag;

	start = clock();
	while (1)
	{
		system("cls");
		gotoxy(0, 4);
		printf("                                                                   \n");
		end = clock();
		gotoxy(60, 0);
		printf("%d\n", (end - start) / CLOCKS_PER_SEC);
		gotoxy(0, 1);
		printf("내 가방 %d/%d\n", n_item, 4);
		printf("장소를 선택하세요.\n\n");
		printf("1. 거실   2. 침실   3. 주방   4. 화장실   5. 방공호       ");

		input = true;
		if (!_kbhit() && input == 1) // 키보드가 눌렸을 때만
		{
			select_place = _getch();
			input = false;
		}


		gotoxy(0, 2);
		printf("                  \n");
		printf("                                                      ");

		input = true;
		//장소 선택
		switch ((int)select_place - 49)
		{
		case LIVING_ROOM:
			ItemChoiceInPlace(pMybag, LIVING_ROOM, pNitem);
			break;
		case BED_ROOM:
			ItemChoiceInPlace(pMybag, BED_ROOM, pNitem);
			break;
		case DIVING_ROOM:
			ItemChoiceInPlace(pMybag, DIVING_ROOM, pNitem);
			break;
		case BATH_ROOM:
			ItemChoiceInPlace(pMybag, BATH_ROOM, pNitem);
			break;;

			/*case SHELTER:
				break;*/
		default:
			break;
		}

		select_place = 0;
		select_item = 0;
		if ((end - start) > (100 * CLOCKS_PER_SEC)) break;

		//Sleep(1);
	}
}

// Place에서 Item 선택하는 함수
void ItemChoiceInPlace(int* pMybag, where place, int* pNitem)
{
	boolean input = true;
	int select_item = 0;
	while (((int)select_item - 48) != 0) //나가기 누르기 전까지
	{
		gotoxy(0, 1);
		printf("내 가방 %d/%d\n", *pNitem, 4);
		input = true;
		gotoxy(0, 2);
		PrintfPlaceItem(place);
		if (!_kbhit() && input == 1) // 키보드가 눌렸을 때만
		{
			select_item = _getch();
			input = false;
		}
		if (*pNitem != 4)
		{
			if (place_item[place][(int)select_item - 49] > 0 && ((int)select_item - 49 < 5))
			{
				++(*pNitem);
				*(pMybag + *pNitem) = place_item[place][(int)select_item - 49];
				place_item[place][(int)select_item - 49] = 0;
				SortZero(place);
			}
			else continue;
		}
		else
		{
			gotoxy(0, 5);
			SetColor(RED);
			printf("가방이 가득 찼습니다. 방공호에 내려놓아야 합니다.\n");
			SetColor(WHITE);
		}
	}

}

// Text color 바꿔주는 함수
void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}