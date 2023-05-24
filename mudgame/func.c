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

// Ŀ�� �̵� �Լ�
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//txt ���� ��� �Լ�
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
		printf("����\n");
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

// Ÿ�̸� �Լ�
unsigned _stdcall TimeCount()
{
	int second = 60;
	while (1)
	{
		gotoxy(80 - 20, 1);
		printf("���� �ð� : %3d��\n", second); // x: ��ü-17
		Sleep(1000); // 1�� ����
		second -= 1; // 1�ʾ� ī��Ʈ

		if (second < 0) break;
	}
	item_choice = false;
	return -1;
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

// Item ��� �Լ�
int PrintfItem(int item)
{
	switch (item)
	{
	case soup:
		printf("����");
		return 2;
		break;
	case water:
		printf("��");
		return 1;
		break;
	case map:
		printf("����");
		return 2;
		break;
	case gas_mask:
		printf("�浶��");
		return 3;
		break;
	case radio:
		printf("����");
		return 3;
		break;
	case ax:
		printf("����");
		return 2;
		break;
	case book:
		printf("å");
		return 1;
		break;
	case checker_board:
		printf("üĿ����");
		return 4;
		break;
	case card:
		printf("ī��");
		return 2;
		break;
	case gun:
		printf("��");
		return 1;
		break;
	case flashlight:
		printf("������");
		return 3;
		break;
	case first_aid_kit:
		printf("���޻���");
		return 4;
		break;
	case bottle:
		printf("����");
		return 2;
		break;
	case megaphone:
		printf("Ȯ����");
		return 3;
		break;
	case empty:
		break;

	default:
		break;
	}
}

// Place ��� �Լ�
void PrintfPlace(int place)
{
	switch (place)
	{
	case LIVING_ROOM:
		SetColor(DarkYellow);
		printf("[�Ž�]\n");
		SetColor(WHITE);
		break;
	case BED_ROOM:
		SetColor(DarkYellow);
		printf("[ħ��]\n");
		SetColor(WHITE);
		break;
	case DINING_ROOM:
		SetColor(DarkYellow);
		printf("[�ֹ�]\n");
		SetColor(WHITE);
		break;
	case BATH_ROOM:
		SetColor(DarkYellow);
		printf("[ȭ���]\n");
		SetColor(WHITE);
		break;
	case SHELTER:
		SetColor(DarkYellow);
		printf("[���ȣ]\n");
		SetColor(WHITE);
		break;
	}
}

// Place �� �������� Item �ִ� �Լ�
void ItemRandom()
{
	srand(time(NULL));

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			//int random = rand() % 10+ 1; //1~10���� �� ����
			int random = rand() % NITEM + 1; //1~100���� �� ����

			if (item_list[random] != 0)
			{
				place_item[i][j] = random;
				item_list[random] -= 1;
			}
			else j--; //�ٽ� �̱�

		}
	}
}

// Place�� �ִ� Item ��� �Լ�
void PrintfPlaceItem(where place, int plus_lines)
{
	PrintfPlace(place);
	printf("\n");
	int item_loc = 0;
	int n_item = 1;
	gotoxy(10, 3 + plus_lines);
	printf("�� ���ư���");
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

// Item�� ���õǾ ����� ������ �� ������ �����ִ� �Լ�
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

// ���� ���� ���
void PrintBag(int* pNitem, int plus_line)
{
	gotoxy(10, 1+ plus_line);
	printf("���� ���� : ");
	for (int i = 0; i < 4; i++)
	{
		if (i >= *pNitem)
		{
			SetColor(GREEN);
			printf("�� ");
		}
		else
		{
			SetColor(RED);
			printf("�� ");
		}
		SetColor(WHITE);
	}
	printf("\n");
}

// Place���� Item �����ϴ� �Լ�
void ItemChoiceInPlace(int* pMybag, where place, int* pNitem, int cols, int lines, int plus_line)
{


	int count_place_item = CountPlaceItem(place);

	int select_item = 0;
	int once = 1;

	while (((int)select_item) != 8 && item_choice) //������ ������ ������
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
				printf("������ ���� á���ϴ�. ���ȣ�� �������ƾ� �մϴ�.\n");
				SetColor(WHITE);
			}
			once = 0;
		}

		if (_kbhit()) // Ű���尡 �ȴ����� ����
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
				printf("������ ���� á���ϴ�. ���ȣ�� �������ƾ� �մϴ�.\n");
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

// ���� ������ �׷��ִ� �Լ�
void DrawStart(int cols, int lines, int* pCL, int* pS, int plus_line)
{
	SetColor(DarkSkyBlue);
	PrintfText("intro_logo.txt", 5, 2 + plus_line); //�ΰ� ���
	SetColor(WHITE);
	char intro_lines[5][200] = { "����� �����Դϴ�.",
		 "��� �ٹ��� �溸�� ��Ƚ��ϴ�!" ,
	 "���� ���ϵǱ���� ���� �ð��� 60�� �Դϴ�.",
	"60�� �ȿ� ������ ���� ���� �������� ì��" ,
		"10�� ���� ���ȣ �ȿ��� �����Ͻʽÿ�." };

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

// ���� ���/ ���� ���� �����ϴ� �Լ�
void MenuChoice(int cols, int lines, int* pCL, int* pS, int plus_line)
{

	int len = 0;
	char game_lines[3][100] = { "���� ���", "         ","���� ����" };
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
		int n = KeyControl(); // Ű���� �̺�Ʈ�� Ű������ �޾ƿ���
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

			if (*pCL > 0) //������ : ���� ����
			{
				system("cls");
				DrawLines(cols, lines);
				*pS = 1;
				return;
			}
			else if (*pCL < 0)
			{// ���� : ���� ���
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

// ���� ��� ��� �Լ�
void PrintHow(int cols, int lines, int plus_line)
{
	system("cls");
	DrawLines(cols, lines);

	SetColor(DarkSkyBlue);
	PrintfText("rex.txt", 5 , 2 + plus_line); //�ΰ� ���
	SetColor(WHITE);
	char intro_lines[5][200] = { "���濡�� �ִ� 4�������� �������� ���� �� �ֽ��ϴ�.",
		 "������ �� ���� ���ȣ�� �������ƾ� �մϴ�." ,
	 "��� �������� ��ҿ� ���� ��ġ�˴ϴ�.",
	"������ ���� ���� �������� ì�� �����Ͻʽÿ�." ,
		"���ư���" };

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

// ����Ű
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

// ���� ���
void PrintMap(int cols, int lines, where place, int plus_line)
{
	int temp_cols = cols;
	int temp_lines = lines;

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			gotoxy(temp_lines, temp_cols+ plus_line);
			if (map_list[i][j] == 9)printf("��");
			else if (map_list[i][j] == 8) printf("��");
			else if (map_list[i][j] == place)
			{
				SetColor(YELLOW);
				printf("��");
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

// ���ȣ�� ������ ��������
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
	printf("���濡 �ִ� ���� ���ȣ �� â��� �ű���� M�� �Է��ϼ���.\n");// m : 109
	gotoxy(17, 28+ plus_line);
	printf("�� �������� ������ S�� �Է��ϼ���. \n"); // h : 115
	SetColor(WHITE);

	gotoxy(10, 2 + plus_line);
	gotoxy(10, 3 + plus_line);
	printf("�� ���� : ");
	gotoxy(10, 4 + plus_line);
	printf("�� ���ư���");
	int once = 1;
	while ((int)select_menu != 8 && item_choice)
	{
		if (once)
		{
			if (*pNitem == 0)
			{
				gotoxy(20, 3 + plus_line);
				SetColor(DarkGreen);
				printf("������ ������ϴ�.                              \n");
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
		if (_kbhit()) // Ű���尡 ������ ����
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


// �� ������ ����ϱ�
void PrintMyItem()
{
	int n_word = 0;
	gotoxy(10, 35);
	printf("�� ������ : ");
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

// 60�� ���� Item �����ϴ� �Լ�
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
			printf("��Ҹ� �����ϼ���.\n\n");
			gotoxy(10, 3 + plus_line);
			printf("1. �Ž�  2. ħ��  3. �ֹ�  4. ȭ���  5. ���ȣ       ");
			once = 0;
		}

		if (_kbhit()) // Ű���尡 ������ ����
		{
			select_place = _getch();
			once = 1;
		}
		else continue;



		gotoxy(0, 2 + plus_line);
		printf("                  \n");

		//��� ����
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

	

	//5�� ����
	for (int i = 1; i < 6; i++)
	{
		int plus_line = 3;
		system("cls");
		DrawLines(cols, lines);

		PrintMyItem();
		PrintHp(*pHp);
		SetColor(DarkSkyBlue);
		gotoxy(3, 1);
		printf("[DAY %2d] - ���ȣ ��", i);
		Sleep(5000);
		SetColor(DarkYellow);
		gotoxy(3, 3 + plus_line);
		printf("[������ �谡 ������.]");
		Sleep(5000);

		SetColor(WHITE);
		if (my_item[soup] > 0)
		{
			gotoxy(3, 5 + plus_line);
			printf("���� �Ѱ��� �Ծ���.");
			total_item--;
			my_item[soup] -= 1;
		}
		else
		{
			gotoxy(3, 5 + plus_line);
			printf("������ ���� ���� HP�� 1 �پ���.");
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

	int random = rand() % 5 + 1; //1~10���� �� ����
	PrintfEvent(random, pHp, plus_line);

}

void PrintfEvent(int number, int* pHp, int plus_line)
{
	switch (number)
	{
	case 1:
		gotoxy(3, 7 + plus_line);
		SetColor(DarkYellow);
		printf("[�㰡 ��Ÿ����.]");
		Sleep(5000);
		gotoxy(3, 9 + plus_line);
		SetColor(WHITE);
		if (my_item[ax] > 0)
		{
			printf("������ ����� �㸦 �׿���.");
			total_item--;
			my_item[ax]--;
		}
		else
		{
			if (my_item[soup] > 0)
			{
				printf("�㰡 ������ �Ծ���.");
				my_item[soup]--;
				total_item--;
			}
			else printf("�㰡 ��������.");
		}
		break;
	case 2:
		gotoxy(3, 7 + plus_line);
		SetColor(DarkYellow);
		printf("[���� ������]");
		Sleep(5000);

		gotoxy(3, 9 + plus_line);
		SetColor(WHITE);
		if (my_item[water] > 0)
		{
			printf("���� ���Ŵ�.");
			total_item--;
			my_item[water]--;
		}
		else
		{
			printf("���� ������ ���� HP�� 1 �پ���.");
			*pHp-=1;
			if (*pHp == 0)return;
			PrintHp(*pHp);
		}
		break;
	case 3:
		gotoxy(3, 7 + plus_line);
		SetColor(DarkYellow);
		printf("[������ ã�ƿԴ�.]");
		srand(time(NULL));
		int random = rand() % 10 + 1; //1~10���� �� ����
		Sleep(5000);

		gotoxy(3, 9 + plus_line);
		SetColor(WHITE);
		if (random > 5)
		{

			printf("������ȯ�� ���ڰ� �Ѵ�.");
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
			printf("��/�� �ְ�");

			SetColor(DarkGreen);

			item_random = rand() % NITEM + 1;
			n_word += PrintfItem(item_random);
			gotoxy(14 + n_word*2, 11 + plus_line);
			my_item[item_random]++;
			gotoxy(14 + n_word*2, 11 + plus_line);
			SetColor(WHITE);
			printf("��/�� ȹ���ߴ�.");
		}
		else
		{
			printf("�����̴�.");
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

					printf("��/�� ���Ѱ��.");
					total_item--;
					break;
				}
			}
		}
		break;
	case 4:
		gotoxy(3, 7 + plus_line);
		SetColor(DarkYellow);
		printf("[�ۿ��� ���Ҹ��� �鸰��.]");
		Sleep(5000);

		gotoxy(3, 9 + plus_line);
		SetColor(WHITE);
		if (my_item[bottle] > 0)
		{
			printf("�������� ���� ȹ���ߴ�.");
			my_item[water]++;
			my_item[bottle]--;

		}
		else
		{
			printf("�ƹ��ϵ� �Ͼ�� �ʾҴ�.");
		}
		break;;
	case 5:
		gotoxy(3, 7 + plus_line);
		SetColor(DarkYellow);
		printf("[�ۿ��� ������ �Ҹ��� �鸰��.]");
		Sleep(5000);

		gotoxy(3, 9 + plus_line);
		SetColor(WHITE);
		if (my_item[megaphone] > 0)
		{
			printf("Ȯ����� ������ ��û�� ������ �޾Ҵ�.");
			my_item[soup]++;
			my_item[megaphone]--;
		}
		else
		{
			printf("�ƹ��ϵ� �Ͼ�� �ʾҴ�.");
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
			printf("��");
		}
		else
		{
			gotoxy(68 + i * 2, 1);
			printf("��");
		}
	}
	SetColor(WHITE);
}