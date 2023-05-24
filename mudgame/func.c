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
#define NITEM 14

boolean item_choice = true;
int item_list[20] = { 0, 10, 10, 1, 1, 1, 1, 1 , 1, 1, 1, 1, 1, 1, 1 };
int place_item[5][5] = { 0 };
int total_item = 0;
int my_item[40] = { 0 };

int map_list[24][30] =
{
   {9,9,9,9,9,9,9,9,9,9, 9,9,9,9,9,9,9,9,9,9, 9,9,9,9,9,9,9,9,9,9},
   {9,4,4,4,4,4,4,4,4,9, 1,1,1,1,1,1,1,1,1,9, 3,3,3,3,3,3,3,3,3,9},
   {9,4,4,4,4,4,4,4,4,8, 1,1,1,1,1,1,1,1,1,8, 3,3,3,3,3,3,3,3,3,9},
   {9,4,4,4,4,4,4,4,4,8, 1,1,1,1,1,1,1,1,1,8, 3,3,3,3,3,3,3,3,3,9},
   {9,4,4,4,4,4,4,4,4,8, 1,1,1,1,1,1,1,1,1,8, 3,3,3,3,3,3,3,3,3,9},
   {9,4,4,4,4,4,4,4,4,9, 1,1,1,1,1,1,1,1,1,9, 3,3,3,3,3,3,3,3,3,9},
   {9,4,4,4,4,4,4,4,4,9, 1,1,1,1,1,1,1,1,1,9, 3,3,3,3,3,3,3,3,3,9},
   {9,9,9,9,9,9,9,9,9,9, 1,1,1,1,1,1,1,1,1,9, 3,3,3,3,3,3,3,3,3,9},
   {9,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,9, 3,3,3,3,3,3,3,3,3,9},
   {9,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,9, 3,3,3,3,3,3,3,3,3,9},
   {9,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,9, 3,3,3,3,3,3,3,3,3,9},
   {9,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,9, 3,3,3,3,3,3,3,3,3,9},
   {9,9,9,9,9,9,9,9,9,9, 9,9,9,9,9,8,8,8,9,9, 9,9,9,9,9,9,9,9,9,9},
   {0,0,0,0,0,0,0,0,0,9, 2,2,2,2,2,2,2,2,2,9, 5,5,5,5,5,5,5,5,5,9},
   {0,0,0,0,0,0,0,0,0,9, 2,2,2,2,2,2,2,2,2,8, 5,5,5,5,5,5,5,5,5,9},
   {0,0,0,0,0,0,0,0,0,9, 2,2,2,2,2,2,2,2,2,8, 5,5,5,5,5,5,5,5,5,9},
   {0,0,0,0,0,0,0,0,0,9, 2,2,2,2,2,2,2,2,2,8, 5,5,5,5,5,5,5,5,5,9},
   {0,0,0,0,0,0,0,0,0,9, 2,2,2,2,2,2,2,2,2,9, 5,5,5,5,5,5,5,5,5,9},
   {0,0,0,0,0,0,0,0,0,9, 2,2,2,2,2,2,2,2,2,9, 5,5,5,5,5,5,5,5,5,9},
   {0,0,0,0,0,0,0,0,0,9, 2,2,2,2,2,2,2,2,2,9, 5,5,5,5,5,5,5,5,5,9},
   {0,0,0,0,0,0,0,0,0,9, 9,9,9,9,9,9,9,9,9,9, 9,9,9,9,9,9,9,9,9,9}
};

int CountPlaceItem(where place)
{
	int count = 0;
	for (int i = 0; i < 5; i++)
	{
		if (place_item[place][i] > 0) count++;
	}
	return count;
}

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
unsigned _stdcall TimeCount()
{
	int second = 60;
	while (1)
	{
		gotoxy(80 - 20, 1);
		printf("남은 시간 : %3d초\n", second); // x: 전체-17
		Sleep(1000); // 1초 지연
		second -= 1; // 1초씩 카운트

		if (second < 0) break;
	}
	item_choice = false;
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
int PrintfItem(int item)
{
	switch (item)
	{
	case soup:
		printf("스프");
		return 2;
		break;
	case water:
		printf("물");
		return 1;
		break;
	case map:
		printf("지도");
		return 2;
		break;
	case gas_mask:
		printf("방독면");
		return 3;
		break;
	case radio:
		printf("라디오");
		return 3;
		break;
	case ax:
		printf("도끼");
		return 2;
		break;
	case book:
		printf("책");
		return 1;
		break;
	case checker_board:
		printf("체커보드");
		return 4;
		break;
	case card:
		printf("카드");
		return 2;
		break;
	case gun:
		printf("총");
		return 1;
		break;
	case flashlight:
		printf("손전등");
		return 3;
		break;
	case first_aid_kit:
		printf("구급상자");
		return 4;
		break;
	case bottle:
		printf("물통");
		return 2;
		break;
	case megaphone:
		printf("확성기");
		return 3;
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
	case DINING_ROOM:
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
			//int random = rand() % 10+ 1; //1~10사이 수 추출
			int random = rand() % NITEM + 1; //1~100사이 수 추출

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
void PrintfPlaceItem(where place, int plus_lines)
{
	PrintfPlace(place);
	printf("\n");
	int item_loc = 0;
	int n_item = 1;
	gotoxy(10, 3 + plus_lines);
	printf("← 돌아가기");
	for (item_loc; item_loc < 5; item_loc++)
	{
		if (place_item[place][item_loc] != 0)
		{
			printf("   %d. ", n_item);
			PrintfItem(place_item[place][item_loc]);
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

// 나의 가방 모양
void PrintBag(int* pNitem, int plus_line)
{
	gotoxy(10, 1+ plus_line);
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

// Place에서 Item 선택하는 함수
void ItemChoiceInPlace(int* pMybag, where place, int* pNitem, int cols, int lines, int plus_line)
{


	int count_place_item = CountPlaceItem(place);

	int select_item = 0;
	int once = 1;

	while (((int)select_item) != 8 && item_choice) //나가기 누르기 전까지
	{
		if (once)
		{
			system("cls");
			DrawLines(cols, lines);

			PrintMap(5, 10, place, plus_line);
			PrintBag(pNitem, 5);

			gotoxy(10, 2 + plus_line);
			PrintfPlaceItem(place, plus_line);

			if (*pNitem == 4)
			{
				gotoxy(13, 27 + plus_line);
				SetColor(RED);
				printf("가방이 가득 찼습니다. 방공호에 내려놓아야 합니다.\n");
				SetColor(WHITE);
			}
			once = 0;
		}

		if (_kbhit()) // 키보드가 안눌렸을 때만
		{
			select_item = _getch();
			once = 1;
		}
		else continue;

		if (((int)select_item - 48 > count_place_item) || ((int)select_item - 48 <= 0)) continue;
		else
		{

			if (*pNitem != 4)
			{
				if (place_item[place][(int)select_item - 49] > 0 && ((int)select_item - 49 < 5))
				{
					*(pMybag + *pNitem) = place_item[place][(int)select_item - 49];
					place_item[place][(int)select_item - 49] = 0;
					++(*pNitem);
					SortZero(place);
				}
				else continue;
			}
			else
			{
				gotoxy(13, 27 + plus_line);
				SetColor(RED);
				printf("가방이 가득 찼습니다. 방공호에 내려놓아야 합니다.\n");
				SetColor(WHITE);
			}
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
					//printf("=");
				}
				else printf(" ");
			}
		}
		printf("\n");
	}



}

// 시작 페이지 그려주는 함수
void DrawStart(int cols, int lines, int* pCL, int* pS, int plus_line)
{
	SetColor(DarkSkyBlue);
	PrintfText("intro_logo.txt", 5, 2 + plus_line); //로고 출력
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
		gotoxy((cols - len) / 2, i + 11+plus_line);
		printf("%s\n", intro_lines[i / 2]);
		i++;
	}

	MenuChoice(cols, lines, pCL, pS, plus_line);
	return;
}

// 게임 방법/ 게임 시작 선택하는 함수
void MenuChoice(int cols, int lines, int* pCL, int* pS, int plus_line)
{

	int len = 0;
	char game_lines[3][100] = { "게임 방법", "         ","게임 시작" };
	for (int i = 0; i < 3; i++) len += strlen(game_lines[i]);

	gotoxy((cols - len) / 2, 23+plus_line);
	SetColor(SkyBlue);
	printf("%s", game_lines[0]);
	SetColor(DarkGray);
	gotoxy((cols - len) / 2 + strlen(game_lines[0]), 23+plus_line);
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
			gotoxy((cols - len) / 2, 23+plus_line);
			SetColor(DarkGray);
			printf("%s%s", game_lines[0], game_lines[1]);
			SetColor(SkyBlue);
			gotoxy((cols - len) / 2 + strlen(game_lines[0]) + strlen(game_lines[1]), 23 + plus_line);
			printf("%s", game_lines[2]);
			SetColor(WHITE);
			*pCL = 1;

			break;
		case LEFT:
			gotoxy((cols - len) / 2, 23 + plus_line);
			SetColor(SkyBlue);
			printf("%s", game_lines[0]);
			SetColor(DarkGray);
			gotoxy((cols - len) / 2 + strlen(game_lines[0]), 23 + plus_line);
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
					PrintHow(cols, lines, plus_line);
					int m = KeyControl();
					if (m == 0)
					{
						system("cls");
						DrawLines(cols, lines);
						DrawStart(cols, lines, pCL, pS, plus_line);
					}
				}
				break;
			}


		}
	}

}

// 게임 방법 출력 함수
void PrintHow(int cols, int lines, int plus_line)
{
	system("cls");
	DrawLines(cols, lines);

	SetColor(DarkSkyBlue);
	PrintfText("rex.txt", 5 , 2 + plus_line); //로고 출력
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
		gotoxy((cols - len) / 2, i + 12 + plus_line);
		if (i / 2 == 4)
		{
			gotoxy((cols - len) / 2, i + 16+ plus_line);
			SetColor(SkyBlue);
		}
		printf("%s\n", intro_lines[i / 2]);
		SetColor(WHITE);
		i++;
	}
}

// 방향키
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

// 지도 출력
void PrintMap(int cols, int lines, where place, int plus_line)
{
	int temp_cols = cols;
	int temp_lines = lines;

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			gotoxy(temp_lines, temp_cols+ plus_line);
			if (map_list[i][j] == 9)printf("■");
			else if (map_list[i][j] == 8) printf("□");
			else if (map_list[i][j] == place)
			{
				SetColor(YELLOW);
				printf("■");
				SetColor(WHITE);
			}
			else printf("  ");


			temp_lines += 2;
		}
		temp_lines = lines;
		temp_cols++;
		printf("\n");
	}

	gotoxy(2 + lines, 1 + cols + plus_line);
	PrintfPlace(BATH_ROOM);
	gotoxy(20 + lines, 1 + cols + plus_line);
	PrintfPlace(LIVING_ROOM);
	gotoxy(20 + lines, 13 + cols + plus_line);
	PrintfPlace(BED_ROOM);
	gotoxy(40 + lines, 1 + cols + plus_line);
	PrintfPlace(DINING_ROOM);
	gotoxy(40 + lines, 13 + cols + plus_line);
	PrintfPlace(SHELTER);

}

// 방공호에 아이템 내려놓기
void PutItemInShelter(int* pMybag, where place, int* pNitem, int cols, int lines, int plus_line)
{
	int select_menu = 0;

	system("cls");
	DrawLines(cols, lines);
	PrintMap(5, 10, place, 5);
	//gotoxy(10, 2);
	//PrintfPlaceItem(place);
	gotoxy(10, 27 + plus_line);
	SetColor(DarkSkyBlue);
	printf("가방에 있는 것을 방공호 내 창고로 옮기려면 M을 입력하세요.\n");// m : 109
	gotoxy(17, 28+ plus_line);
	printf("내 아이템을 보려면 S를 입력하세요. \n"); // h : 115
	SetColor(WHITE);

	gotoxy(10, 2 + plus_line);
	gotoxy(10, 3 + plus_line);
	printf("내 가방 : ");
	gotoxy(10, 4 + plus_line);
	printf("← 돌아가기");
	int once = 1;
	while ((int)select_menu != 8 && item_choice)
	{
		if (once)
		{
			if (*pNitem == 0)
			{
				gotoxy(20, 3 + plus_line);
				SetColor(DarkGreen);
				printf("가방이 비었습니다.                              \n");
				SetColor(WHITE);
			}

			int n_word = 0;
			for (int item_loc = 0; item_loc < 4; item_loc++)
			{
				gotoxy(20 + n_word * 2 + item_loc, 3 + plus_line);
				n_word += PrintfItem(pMybag[item_loc]);
				gotoxy(20 + n_word * 2 + item_loc, 3 + plus_line);
				if (pMybag[item_loc] != 0)printf(" ");
			}
			once = 0;
		}
		if (_kbhit()) // 키보드가 눌렸을 때만
		{
			select_menu = _getch();
			once = 1;
		}
		else continue;

		if (select_menu == 109)
		{
			for (int i = 0; i < 4; i++)
			{
				my_item[pMybag[i]] += 1;
				pMybag[i] = 0;
				total_item++;
			}
			*pNitem = 0;

		}
		else if (select_menu == 115) PrintMyItem();
		else continue;
	}

}


// 내 아이템 출력하기
void PrintMyItem()
{
	int n_word = 0;
	gotoxy(10, 35);
	printf("내 아이템 : ");
	int line = 0;
	int count = 0;
	for (int i = 1; i <= NITEM; i++)
	{
		if (35 + n_word * 2 > 80)
		{
			n_word = 0;
			line += 2;
		}


		if (my_item[i] != 0)
		{
			gotoxy(22 + n_word * 2, 35 + line);
			n_word += PrintfItem(i);
			if (my_item[i] != 1)
			{
				gotoxy(23 + n_word * 2, 35 + line);
				printf("%d", my_item[i]);
				n_word++;
			}
			n_word++;
		}

		//n_word++;

	}
}

// 60초 동안 Item 선택하는 함수
void ItemChoice(int cols, int lines, int plus_line)
{
	char select_place;
	char select_item;
	int n_item = 0;
	int* pNitem = &n_item;
	int my_bag[4] = { 0 };
	int* pMybag = my_bag;

	clock_t start, end;

	_beginthreadex(NULL, 0, TimeCount, 0, 0, NULL);

	int once = 1;

	while (item_choice)
	{
		if (once)
		{
			system("cls");
			DrawLines(cols, lines);
			PrintMap(5, 10, 100,5);
			gotoxy(0, 4 + plus_line);
			printf("                                                                   \n");
			gotoxy(60, 1 + plus_line);
			PrintBag(pNitem, 5);
			gotoxy(10, 2 + plus_line);
			printf("장소를 선택하세요.\n\n");
			gotoxy(10, 3 + plus_line);
			printf("1. 거실  2. 침실  3. 주방  4. 화장실  5. 방공호       ");
			once = 0;
		}

		if (_kbhit()) // 키보드가 눌렸을 때만
		{
			select_place = _getch();
			once = 1;
		}
		else continue;



		gotoxy(0, 2 + plus_line);
		printf("                  \n");

		//장소 선택
		switch ((int)select_place - 48)
		{
		case LIVING_ROOM:
			ItemChoiceInPlace(pMybag, LIVING_ROOM, pNitem, cols, lines, 5);
			break;
		case BED_ROOM:
			ItemChoiceInPlace(pMybag, BED_ROOM, pNitem, cols, lines, 5);
			break;
		case DINING_ROOM:
			ItemChoiceInPlace(pMybag, DINING_ROOM, pNitem, cols, lines, 5);
			break;
		case BATH_ROOM:
			ItemChoiceInPlace(pMybag, BATH_ROOM, pNitem, cols, lines, 5);
			break;;

		case SHELTER:
			PutItemInShelter(pMybag, SHELTER, pNitem, cols, lines, 5);
			break;
		default:
			break;
		}

		select_place = 0;
		select_item = 0;



		//Sleep(1);
	}
}

void ShelterPage(int cols, int lines, int * pHp)
{

	

	//5일 동안
	for (int i = 1; i < 6; i++)
	{
		int plus_line = 3;
		system("cls");
		DrawLines(cols, lines);

		PrintMyItem();
		PrintHp(*pHp);
		SetColor(DarkSkyBlue);
		gotoxy(3, 1);
		printf("[DAY %2d] - 방공호 안", i);
		Sleep(5000);
		SetColor(DarkYellow);
		gotoxy(3, 3 + plus_line);
		printf("[렉스는 배가 고프다.]");
		Sleep(5000);

		SetColor(WHITE);
		if (my_item[soup] > 0)
		{
			gotoxy(3, 5 + plus_line);
			printf("스프 한개를 먹었다.");
			total_item--;
			my_item[soup] -= 1;
		}
		else
		{
			gotoxy(3, 5 + plus_line);
			printf("스프를 먹지 못해 HP가 1 줄었다.");
			*pHp -= 1;
			if (*pHp == 0) return;
			PrintHp(*pHp);
		}

		Sleep(5000);
		EventRandom(pHp, plus_line);
		Sleep(5000);

	}
}

void EventRandom(int* pHp, int plus_line)
{
	srand(time(NULL));

	int random = rand() % 5 + 1; //1~10사이 수 추출
	PrintfEvent(random, pHp, plus_line);

}

void PrintfEvent(int number, int* pHp, int plus_line)
{
	switch (number)
	{
	case 1:
		gotoxy(3, 7 + plus_line);
		SetColor(DarkYellow);
		printf("[쥐가 나타났다.]");
		Sleep(5000);
		gotoxy(3, 9 + plus_line);
		SetColor(WHITE);
		if (my_item[ax] > 0)
		{
			printf("도끼를 사용해 쥐를 죽였다.");
			total_item--;
			my_item[ax]--;
		}
		else
		{
			if (my_item[soup] > 0)
			{
				printf("쥐가 스프를 먹었다.");
				my_item[soup]--;
				total_item--;
			}
			else printf("쥐가 도망갔다.");
		}
		break;
	case 2:
		gotoxy(3, 7 + plus_line);
		SetColor(DarkYellow);
		printf("[목이 마르다]");
		Sleep(5000);

		gotoxy(3, 9 + plus_line);
		SetColor(WHITE);
		if (my_item[water] > 0)
		{
			printf("물을 마신다.");
			total_item--;
			my_item[water]--;
		}
		else
		{
			printf("물을 마시지 못해 HP가 1 줄었다.");
			*pHp-=1;
			if (*pHp == 0)return;
			PrintHp(*pHp);
		}
		break;
	case 3:
		gotoxy(3, 7 + plus_line);
		SetColor(DarkYellow);
		printf("[누군가 찾아왔다.]");
		srand(time(NULL));
		int random = rand() % 10 + 1; //1~10사이 수 추출
		Sleep(5000);

		gotoxy(3, 9 + plus_line);
		SetColor(WHITE);
		if (random > 5)
		{

			printf("물물교환을 하자고 한다.");
			Sleep(5000);
			int item_random = 0;
			int n_word = 0;
			gotoxy(3, 11 + plus_line);
			SetColor(DarkGreen);
			while (1)
			{
				item_random = rand() % NITEM + 1;
				n_word = PrintfItem(item_random);
				if (my_item[item_random] <= 0) continue;
				else
				{
					my_item[item_random]--;
					gotoxy(3 + n_word*2, 11 + plus_line);
					break;
				}
			}
			SetColor(WHITE);
			printf("을/를 주고");

			SetColor(DarkGreen);

			item_random = rand() % NITEM + 1;
			n_word += PrintfItem(item_random);
			gotoxy(14 + n_word*2, 11 + plus_line);
			my_item[item_random]++;
			gotoxy(14 + n_word*2, 11 + plus_line);
			SetColor(WHITE);
			printf("을/를 획득했다.");
		}
		else
		{
			printf("도둑이다.");
			Sleep(5000);
			SetColor(DarkGreen);

			while (1)
			{
				int item_random = rand() % NITEM + 1;
				gotoxy(3, 11 + plus_line);
				int n_word = PrintfItem(item_random);
				if (my_item[item_random] <= 0) continue;
				else
				{
					my_item[item_random]--;
					gotoxy(3 + n_word *2, 11 + plus_line);
					SetColor(WHITE);

					printf("을/를 빼앗겼다.");
					total_item--;
					break;
				}
			}
		}
		break;
	case 4:
		gotoxy(3, 7 + plus_line);
		SetColor(DarkYellow);
		printf("[밖에서 빗소리가 들린다.]");
		Sleep(5000);

		gotoxy(3, 9 + plus_line);
		SetColor(WHITE);
		if (my_item[bottle] > 0)
		{
			printf("물통으로 물을 획득했다.");
			my_item[water]++;
			my_item[bottle]--;

		}
		else
		{
			printf("아무일도 일어나지 않았다.");
		}
		break;;
	case 5:
		gotoxy(3, 7 + plus_line);
		SetColor(DarkYellow);
		printf("[밖에서 구조대 소리가 들린다.]");
		Sleep(5000);

		gotoxy(3, 9 + plus_line);
		SetColor(WHITE);
		if (my_item[megaphone] > 0)
		{
			printf("확성기로 도움을 요청해 스프를 받았다.");
			my_item[soup]++;
			my_item[megaphone]--;
		}
		else
		{
			printf("아무일도 일어나지 않았다.");
		}
		break;;
	}

}

void PrintHp(int hp)
{
	for (int i = 0; i < 5; i++)
	{
		SetColor(DarkRed);
		if (hp > i)
		{
			gotoxy(68 + i * 2, 1);
			printf("♥");
		}
		else
		{
			gotoxy(68 + i * 2, 1);
			printf("♡");
		}
	}
	SetColor(WHITE);
}