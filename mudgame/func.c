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

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 0


int item_list[20] = { 0, 10, 10, 1, 1, 1, 1, 1 , 1, 1, 1, 1, 1, 1, 1 };
int place_item[5][5] = { 0 };
int total_item = 0;
int my_item[40] = { 0 };

// 커서 이동 함수
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//txt 파일 출력 함수
void PrintfText(char* file_name, int cols, int lines)
{
	FILE* fp;
	int count = 0;
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
		gotoxy(cols, lines + count);
		printf(str);
		count++;
	}
	puts("");

	fclose(fp);
}

// 타이머 함수
int TimeCount(int second)
{
	while (1)
	{
		gotoxy(80 - 20, 2);
		printf("남은 시간 : %d초\n", second); // x: 전체-17
		Sleep(1000); // 1초 지연
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

void PrintBag(int* pNitem)
{
	gotoxy(5, 1);
	printf("나의 가방 : ");
	for (int i = 0; i < 4; i++)
	{
		if (i >= *pNitem)
		{
			SetColor(GREEN);
			printf("□ ");
		}
		else
		{
			SetColor(RED);
			printf("■ ");
		}
		SetColor(WHITE);
	}
	printf("\n");
}



// 60초 동안 Item 선택하는 함수
void ItemChoice(cols, lines)
{
	boolean input = true;

	char select_place;
	char select_item;
	int n_item = 0;
	int* pNitem = &n_item;
	int my_bag[4] = { 0 };
	int* pMybag = my_bag;

	clock_t start, end;

	while (1)
	{
		system("cls");
		DrawLines(cols, lines);
		gotoxy(0, 4);
		printf("                                                                   \n");
		gotoxy(60, 0);
		gotoxy(0, 1);
		PrintBag(pNitem);
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
		//printf("                                                      ");

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
		PrintBag(pNitem);

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
			gotoxy(0, 6);
			SetColor(RED);
			printf("가방이 가득 찼습니다. 방공호에 내려놓아야 합니다.\n");
			SetColor(WHITE);
		}
	}

}

// Text color
void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// int cols = 80, lines = 30;
void DrawLines(int cols, int lines)
{
	for (int i = 0; i < lines - 1; i++)
	{
		for (int j = 0; j < cols - 1; j++)
		{
			if (i == 0 || i == lines - 2)
			{
				printf("=");
			}
			else
			{
				if (j == 0 || j == cols - 2)
				{
					printf("=");
				}
				else printf(" ");
			}
		}
		printf("\n");
	}



}

// 시작 페이지 그려주는 함수
void DrawStart(int cols, int lines, int* pCL, int* pS)
{
	SetColor(DarkSkyBlue);
	PrintfText("intro_logo.txt", 8, 2); //로고 출력
	SetColor(WHITE);
	char intro_lines[5][200] = { "당신은 렉스입니다.",
		 "방금 핵무기 경보가 울렸습니다!" ,
	 "핵이 투하되기까지 남은 시간은 60초 입니다.",
	"60초 안에 가능한 많은 생존 아이템을 챙겨" ,
		"10일 동안 방공호 안에서 생존하십시오." };

	int len = 0;
	for (int i = 0; i < 10; i++)
	{
		len = strlen(intro_lines[i / 2]);
		gotoxy((cols - len) / 2, i + 11);
		printf("%s\n", intro_lines[i / 2]);
		i++;
	}

	MenuChoice(cols, lines, pCL, pS);
	return;
}

// 게임 방법/ 게임 시작 선택하는 함수
void MenuChoice(int cols, int lines, int* pCL, int* pS)
{

	int len = 0;
	char game_lines[3][100] = { "게임 방법", "         ","게임 시작" };
	for (int i = 0; i < 3; i++) len += strlen(game_lines[i]);

	gotoxy((cols - len) / 2, 23);
	SetColor(SkyBlue);
	printf("%s", game_lines[0]);
	SetColor(DarkGray);
	gotoxy((cols - len) / 2 + strlen(game_lines[0]), 23);
	printf("%s%s", game_lines[1], game_lines[2]);
	SetColor(WHITE);

	while (1)
	{
		int n = KeyControl(); // 키보드 이벤트를 키값으로 받아오기
		switch (n)
		{
		default:
			break;
		case RIGHT:
			gotoxy((cols - len) / 2, 23);
			SetColor(DarkGray);
			printf("%s%s", game_lines[0], game_lines[1]);
			SetColor(SkyBlue);
			gotoxy((cols - len) / 2 + strlen(game_lines[0]) + strlen(game_lines[1]), 23);
			printf("%s", game_lines[2]);
			SetColor(WHITE);
			*pCL = 1;

			break;
		case LEFT:
			gotoxy((cols - len) / 2, 23);
			SetColor(SkyBlue);
			printf("%s", game_lines[0]);
			SetColor(DarkGray);
			gotoxy((cols - len) / 2 + strlen(game_lines[0]), 23);
			printf("%s%s", game_lines[1], game_lines[2]);
			SetColor(WHITE);
			*pCL = -1;

			break;

		case ENTER:

			if (*pCL > 0) //오른쪽 : 게임 시작
			{
				system("cls");
				DrawLines(cols, lines);
				*pS = 1;
				return;
			}
			else if (*pCL < 0)
			{// 왼쪽 : 게임 방법
				while (1)
				{
					if (*pS == 1) return;
					PrintHow(cols, lines);
					int m = KeyControl();
					if (m == 0)
					{
						system("cls");
						DrawLines(cols, lines);
						DrawStart(cols, lines, pCL, pS);
					}
				}
				break;
			}


		}
	}

}

// 게임 방법 출력 함수
void PrintHow(int cols, int lines)
{
	system("cls");
	DrawLines(cols, lines);

	SetColor(DarkSkyBlue);
	PrintfText("intro_logo.txt", 8, 2); //로고 출력
	SetColor(WHITE);
	char intro_lines[5][200] = { "가방에는 최대 4개까지만 아이템을 담을 수 있습니다.",
		 "가방이 꽉 차면 방공호에 내려놓아야 합니다." ,
	 "모든 아이템은 장소에 랜덤 배치됩니다.",
	"가능한 많은 생존 아이템을 챙겨 생존하십시오." ,
		"돌아가기" };

	int len = 0;
	for (int i = 0; i < 10; i++)
	{
		len = strlen(intro_lines[i / 2]);
		gotoxy((cols - len) / 2, i + 11);
		if (i / 2 == 4)
		{
			gotoxy((cols - len) / 2, i + 15);
			SetColor(SkyBlue);
		}
		printf("%s\n", intro_lines[i / 2]);
		SetColor(WHITE);
		i++;
	}
}


int KeyControl()
{
	char key = _getch();
	if (_kbhit())
	{
		if (key == -32)
		{
			key = _getch();
		}
		else if (key == '\n') return 0;

	}
}

void PrintMap()
{
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                   □               □                      ■\n");
	printf("■                   □               □                      ■\n");
	printf("■                   □               □                      ■\n");
	printf("■                   ■               ■                      ■\n");
	printf("■                   ■               ■                      ■\n");
	printf("■■■■■■■■■■■                ■                      ■\n");
	printf("■                                    ■■■■■■■■■■■■■\n");
	printf("■                                    ■\n");
	printf("■                                    ■\n");
	printf("■                                    ■\n");
	printf("■■■■■■■■■■■■■■□□□■■■\n");
	printf("                   ■                 ■\n");
	printf("                   ■                 ■\n");
	printf("                   ■                 ■\n");
	printf("                   ■                 ■\n");
	printf("                   ■                 ■\n");
	printf("                   ■                 ■\n");
	printf("                   ■■■■■■■■■■\n");
}