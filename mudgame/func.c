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

// Ŀ�� �̵� �Լ�
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//txt ���� ��� �Լ�
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
		printf("����\n");
		exit(1);
	}

	while (fgets(str, 255, fp) != NULL)
	{
		printf(str);
	}
	puts("");

	fclose(fp);
}

// Ÿ�̸� �Լ�
int TimeCount(int second)
{
	while (1)
	{
		gotoxy(100 - 17, 1);
		printf("���� �ð� : %d��\n", second); // x: ��ü-17
		Sleep(1000); // 1�� ����

		gotoxy(100 - 17, 1);
		printf("                \n");
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

// 60�� ���� Item �����ϴ� �Լ�
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
		printf("�� ���� %d/%d\n", n_item, 4);
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
		printf("                                                      ");

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
		if ((end - start) > (100 * CLOCKS_PER_SEC)) break;

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
		gotoxy(0, 1);
		printf("�� ���� %d/%d\n", *pNitem, 4);
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
			gotoxy(0, 5);
			SetColor(RED);
			printf("������ ���� á���ϴ�. ���ȣ�� �������ƾ� �մϴ�.\n");
			SetColor(WHITE);
		}
	}

}

// Text color �ٲ��ִ� �Լ�
void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}