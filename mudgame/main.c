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
	// �ʱ� ȭ�� ����
	system("mode con: cols=80 lines=40");  //cols = ĭ/�� (����)  lines = ��/�� (����)
	SetConsoleTitle(TEXT("Last Choice"));
	CursorView(false);

	// �޴� ����
	int cursor_loc = -1;
	int* pCL = &cursor_loc;
	int start = 0;
	int* pS = &start;
	int hp = 5;
	int* pHp = &hp;

	
	/*
	DrawLines(cols, lines);
	DrawStart(cols, lines, pCL, pS, 5);

	// ���� ����
	DrawLines(cols, lines);

	// ������ ���� - �� ��ҿ� �������� ������ ����
	ItemRandom();

	// 60�� ���� ������ ����
	ItemChoice(cols, lines, 5);

	// ���ȣ���� 10��
	ShelterPage(cols, lines, pHp);
	system("cls");
	
	*/
	//���� ��
	if (hp == 0)
	{
		PrintfText("lose.txt", cols, lines); //�ΰ� ���
		gotoxy(30, 35);
		printf("���[����]�� �׾����ϴ�.");
		Sleep(500000);
	}
	else
	{
		PrintfText("win.txt", cols, lines); //�ΰ� ���
		gotoxy(25, 25);
		printf("�����մϴ�. ������ �����߽��ϴ�.");
		Sleep(500000);
	}

}


