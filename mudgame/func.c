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
int TimeCount(int second)
{
	while (1)
	{
		gotoxy(80 - 20, 2);
		printf("���� �ð� : %d��\n", second); // x: ��ü-17
		Sleep(1000); // 1�� ����
		second -= 1; // 1�ʾ� ī��Ʈ

		if (second < 0) break;
	}
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
int PrintfItem(int place, int item_loc)
{
	switch (place_item[place][item_loc])
	{
	case soup:
		printf("����");
		break;
	case water:
		printf("��");
		break;
	case map:
		printf("����");
		break;
	case gas_mask:
		printf("�浶��");
		break;
	case radio:
		printf("����");
		break;
	case ax:
		printf("����");
		break;
	case book:
		printf("å");
		break;
	case checker_board:
		printf("üĿ����");
		break;
	case card:
		printf("ī��");
		break;
	case gun:
		printf("��");
		break;
	case flashlight:
		printf("������");
		break;
	case first_aid_kit:
		printf("���޻���");
		break;
	case bottle:
		printf("����");
		break;
	case megaphone:
		printf("Ȯ����");
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
	case DIVING_ROOM:
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
			int random = rand() % 10 + 1; //1~10���� �� ����
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
void PrintfPlaceItem(where place)
{
	PrintfPlace(place);
	printf("\n");
	int item_loc = 0;
	int n_item = 1;
	printf("0. ���ư���");
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

void PrintBag(int* pNitem)
{
	gotoxy(5, 1);
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



// 60�� ���� Item �����ϴ� �Լ�
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
		printf("��Ҹ� �����ϼ���.\n\n");
		printf("1. �Ž�   2. ħ��   3. �ֹ�   4. ȭ���   5. ���ȣ       ");

		input = true;
		if (!_kbhit() && input == 1) // Ű���尡 ������ ����
		{
			select_place = _getch();
			input = false;
		}


		gotoxy(0, 2);
		printf("                  \n");
		//printf("                                                      ");

		input = true;
		//��� ����
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

// Place���� Item �����ϴ� �Լ�
void ItemChoiceInPlace(int* pMybag, where place, int* pNitem)
{
	boolean input = true;
	int select_item = 0;
	while (((int)select_item - 48) != 0) //������ ������ ������
	{
		PrintBag(pNitem);

		input = true;
		gotoxy(0, 2);
		PrintfPlaceItem(place);
		if (!_kbhit() && input == 1) // Ű���尡 ������ ����
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
			printf("������ ���� á���ϴ�. ���ȣ�� �������ƾ� �մϴ�.\n");
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

// ���� ������ �׷��ִ� �Լ�
void DrawStart(int cols, int lines, int* pCL, int* pS)
{
	SetColor(DarkSkyBlue);
	PrintfText("intro_logo.txt", 8, 2); //�ΰ� ���
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
		gotoxy((cols - len) / 2, i + 11);
		printf("%s\n", intro_lines[i / 2]);
		i++;
	}

	MenuChoice(cols, lines, pCL, pS);
	return;
}

// ���� ���/ ���� ���� �����ϴ� �Լ�
void MenuChoice(int cols, int lines, int* pCL, int* pS)
{

	int len = 0;
	char game_lines[3][100] = { "���� ���", "         ","���� ����" };
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
		int n = KeyControl(); // Ű���� �̺�Ʈ�� Ű������ �޾ƿ���
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

// ���� ��� ��� �Լ�
void PrintHow(int cols, int lines)
{
	system("cls");
	DrawLines(cols, lines);

	SetColor(DarkSkyBlue);
	PrintfText("intro_logo.txt", 8, 2); //�ΰ� ���
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
	printf("���������������������������������\n");
	printf("��                   ��               ��                      ��\n");
	printf("��                   ��               ��                      ��\n");
	printf("��                   ��               ��                      ��\n");
	printf("��                   ��               ��                      ��\n");
	printf("��                   ��               ��                      ��\n");
	printf("������������                ��                      ��\n");
	printf("��                                    ��������������\n");
	printf("��                                    ��\n");
	printf("��                                    ��\n");
	printf("��                                    ��\n");
	printf("���������������������\n");
	printf("                   ��                 ��\n");
	printf("                   ��                 ��\n");
	printf("                   ��                 ��\n");
	printf("                   ��                 ��\n");
	printf("                   ��                 ��\n");
	printf("                   ��                 ��\n");
	printf("                   �����������\n");
}